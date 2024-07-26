#ifndef  SRC_OBJECTS_BEHAVIORAL_COR__
#define SRC_OBJECTS_BEHAVIORAL_COR__

// Chain of Responsibility pattern

#include <string>

// TODO: make Response and Request interfaces
using Request = std::string;
using Response = std::string;

class IHandler {
	public:
		virtual Response Handle(Request) = 0;
		virtual IHandler* SetNext(IHandler*) = 0;
		virtual ~IHandler() = default;
};

class Handler: public IHandler {
	public:
		virtual Response Handle(Request) override;
		virtual IHandler* SetNext(IHandler*) override;
		virtual ~Handler() = default;
	protected:
		Handler(); 
	private:
		IHandler* _next_handler;
};

#endif // SRC_OBJECTS_BEHAVIORAL_COR__
