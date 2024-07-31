#ifndef SRC_BEHAVIORAL_COR__
#define SRC_BEHAVIORAL_COR__

// Chain of Responsibility pattern

template <typename T, typename U>
class IHandler {
 public:
  // Explicit default constructor
  IHandler() = default;

  // Virtual destructor
  virtual ~IHandler() = default;

  // Non-Copyable
  IHandler(const IHandler&) = delete;
  auto operator=(const IHandler&) -> IHandler& = delete;

  // Non-Movable
  IHandler(IHandler&&) = delete;
  auto operator=(IHandler&&) -> IHandler& = delete;

  // Pure virtual functions
  virtual auto Handle(T) -> U = 0;
  virtual auto SetNext(IHandler<T, U>*) -> IHandler<T, U>* = 0;
};

template <typename T, typename U>
class Handler : public IHandler<T, U> {
 public:
  auto Handle(T) -> U override;
  auto SetNext(IHandler<T, U>*) -> IHandler<T, U>* override;

  ~Handler() override = default;

  // Non-Copyable
  Handler(const Handler&) = delete;
  auto operator=(const Handler&) -> Handler& = delete;

  // Non-Movable
  Handler(Handler&&) = delete;
  auto operator=(Handler&&) -> Handler& = delete;

 protected:
  Handler() = default;

 private:
  IHandler<T, U>* _next_handler{};
};

template <typename T, typename U>
auto Handler<T, U>::Handle(T req) -> U {
  if (_next_handler) {
    return _next_handler->Handle(req);
  }

  return U{};
}

template <typename T, typename U>
auto Handler<T, U>::SetNext(IHandler<T, U>* next_handler) -> IHandler<T, U>* {
  _next_handler = next_handler;
  return _next_handler;
}

#endif  // SRC_BEHAVIORAL_COR__
