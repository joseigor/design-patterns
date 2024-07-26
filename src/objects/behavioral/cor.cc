#include "cor.hpp"

Handler::Handler():_next_handler{nullptr}{}

Response Handler::Handle(Request req) {
	if(_next_handler){
		return _next_handler->Handle(req);
	}

	return Response{};
}

IHandler* Handler::SetNext(IHandler* next_handler){
	_next_handler = next_handler;
	return _next_handler;
}
