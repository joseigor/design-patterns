#include <gtest/gtest.h>
#include <cor.hpp>
#include <string>

class ConcretHandler : public Handler {
	public:
	ConcretHandler(const std::string &help_message = ""): _help_message{help_message}{}
	
	virtual ~ConcretHandler() = default;

	virtual Response Handle(Request req) override {
		if(!_help_message.empty()) {
			return Response{_help_message};
		} else {
			return Handler::Handle(req);
		}
	}
	
	private:
	std::string _help_message;
}; 


TEST(ChainOfResposibility, ReturnEmptyStringWhenThereIsNoHandle) {
	std::string expected_helper_text{""};
	ConcretHandler ch{};
	EXPECT_EQ(expected_helper_text, ch.Handle({}));
}

TEST(ChainOfResposibility, ReturnHelperStringWhenThereIsOne) {
	std::string expected_helper_text{"This is a helper text!"};
	ConcretHandler ch{expected_helper_text};
	EXPECT_EQ(expected_helper_text, ch.Handle({}));
}

TEST(ChainOfResposibility, ReturnHelperStringFromTheLastHandler) {
	std::string expected_helper_text{"This is a helper text!"};
	ConcretHandler ch_1{};
	ConcretHandler ch_2{};
	ConcretHandler ch_3{expected_helper_text};
	
	// set the handler chain
	ch_1.SetNext(&ch_2);
	ch_2.SetNext(&ch_3);

	EXPECT_EQ(expected_helper_text, ch_1.Handle({}));
}

TEST(ChainOfResposibility, RequestIsNotHandledByTheLastHandler) {
	std::string expected_helper_text{""};
	ConcretHandler ch_1{};
	ConcretHandler ch_2{};
	ConcretHandler ch_3{};
	
	// set the handler chain
	ch_1.SetNext(&ch_2);
	ch_2.SetNext(&ch_3);

	EXPECT_EQ(expected_helper_text, ch_1.Handle({}));
}
