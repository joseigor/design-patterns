#ifndef  SRC_BEHAVIORAL_COR__
#define  SRC_BEHAVIORAL_COR__

// Chain of Responsibility pattern


template<typename T, typename U>
class IHandler {
	public:
		virtual U Handle(T) = 0;
		virtual IHandler<T, U>* SetNext(IHandler<T, U>*) = 0;
	protected:
		virtual ~IHandler() = default;
};

template<typename T, typename U>
class Handler: public IHandler<T, U> {
	public:
		virtual U Handle(T) override;
		virtual IHandler<T, U>* SetNext(IHandler<T, U>*) override;
		virtual ~Handler() = default;
	protected:
		Handler(); 
	private:
		IHandler<T, U>* _next_handler;
};

template<typename T, typename U>
Handler<T, U>::Handler():_next_handler{nullptr}{}

template<typename T, typename U>
U Handler<T, U>::Handle(T req)  {
	if(_next_handler){
		return _next_handler->Handle(req);
	}

	return U{};
}

template<typename T, typename U>
IHandler<T, U>* Handler<T, U>::SetNext(IHandler<T, U>* next_handler){
	_next_handler = next_handler;
	return _next_handler;
}

#endif // SRC_BEHAVIORAL_COR__
