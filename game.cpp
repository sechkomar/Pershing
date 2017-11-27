#include <list>
#include "objects.h"
#include "game.h"



void game::getMap()
{
	json jLayer0;
	jLayer0["layer"] = 0;

	std::string strLayer0 = jLayer0.dump();
	ActionMessage act(Action::MAP, strLayer0);
	ResponseMessage resp;
	socket.MakeMove(act, resp);
	//TODO save map
	
	json jMapResp(resp.data);

	std::list<Line> lines = jMapResp.at("line").get<std::list<Line>>();
	
	for (auto line : lines)
	{
		Endpoint in, out;
		in.line_idx = line.idx;
		in.end = line.point.second;
		in.length = line.length;
		in.direction = 1;
		map[line.point.first].push_back(in);
		
		out.line_idx = line.idx;
		out.end = line.point.first;
		out.length = line.length;
		out.direction = -1;
		map[line.point.second].push_back(out);
	}
}

bool game::init()
{
	const char* HOST_NAME = "wgforge-srv.wargaming.net";
	const char* PORT = "443";
	if (socket.Connect(HOST_NAME, PORT))
	{
		std::cout << "Error while connecting." << std::endl;
		return false;
	}

	json jLogin;
	jLogin["name"] = "Boris";

	std::string strLogin = jLogin.dump();
	ActionMessage act(Action::LOGIN, strLogin);

	ResponseMessage resp;
	socket.MakeMove(act, resp);

	if (!resp.dataLength)
		return false;

	json jLoginResp(resp.data);

	home.idx = jLoginResp["home"]["idx"].get<uint32_t>();
	home.post_id = jLoginResp["home"]["post_id"].get<uint32_t>();
	idx = jLoginResp["idx"].get<std::string>();

	std::list<Train> trainsList;
	trainsList = jLoginResp["train"].get<std::list<Train>>();
	
	for (auto train : trainsList)
	{
		trains[train.idx] = train;
	}

	return true;
}

void game::move(uint32_t line_idx, int speed, uint32_t train_idx)
{
	// TODO CHECK IT TOO
	json jMove = json({ { "line_idx", line_idx },{ "speed", speed },{ "train_idx", train_idx } });
	std::string strMove = jMove.dump();
	ActionMessage act = ActionMessage(Action::MOVE, strMove);
	socket.Send(act);
}

void game::turn()
{
	// TODO: CHECK IT
	ActionMessage act = ActionMessage(Action::TURN, std::string(""));
	socket.Send(act);
}

int game::end()
{
	ActionMessage act = ActionMessage(Action::LOGOUT, std::string());
	ResponseMessage resp;
	socket.MakeMove(act, resp);

	socket.Disconnect();
	return EXIT_SUCCESS;
}

