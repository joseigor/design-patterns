#include <gtest/gtest.h>
#include <cor.hpp>
#include <string>

class HandlerStringReq : public Handler<std::string, std::string> {
	public:
	HandlerStringReq(const std::string &help_message = ""): _help_message{help_message}{}
	
	virtual ~HandlerStringReq() = default;

	virtual std::string Handle(std::string req) override {
		if(!_help_message.empty()) {
			return std::string{_help_message};
		} else {
			return Handler::Handle(req);
		}
	}
	
	private:
	std::string _help_message;
}; 


class HandlerIntReq: public Handler<int, std::string> {
	public:
	HandlerIntReq(int req): _req{req}{}
	
	virtual ~HandlerIntReq() = default;


	virtual std::string Handle(int req) override {
		if(req == _req){
			return std::to_string(req);
 		}

		return Handler::Handle(req);
	}

	private:
	int  _req;
};

TEST(ChainOfResposibility, ReturnEmptyStringWhenThereIsNoHandle) {
	// Test the string request handler
	std::string expected_helper_text{""};
	HandlerStringReq ch{};
	EXPECT_EQ(expected_helper_text, ch.Handle({}));
	
	// Test the int request handler
	HandlerIntReq ih{1};
	EXPECT_EQ(expected_helper_text, ih.Handle(0));
}

TEST(ChainOfResposibility, ReturnHelperStringWhenThereIsOne) {
	// Test the string request handler
	std::string expected_helper_text{"This is a helper text!"};
	HandlerStringReq ch{expected_helper_text};
	EXPECT_EQ(expected_helper_text, ch.Handle({}));

	// Test the int request handler
	HandlerIntReq ih{1};
	EXPECT_EQ("1", ih.Handle(1));
}

TEST(ChainOfResposibility, ReturnHelperStringFromTheLastHandler) {
	// Test the string request handler
	std::string expected_helper_text{"This is a helper text!"};
	HandlerStringReq ch_1{};
	HandlerStringReq ch_2{};
	HandlerStringReq ch_3{expected_helper_text};
	// set the handler chain
	ch_1.SetNext(&ch_2)->SetNext(&ch_3);
	EXPECT_EQ(expected_helper_text, ch_1.Handle({}));

	// Test the int request handler
	HandlerIntReq ih_1{1};
	HandlerIntReq ih_2{2};
	HandlerIntReq ih_3{3};
	// set the handler chain
	ih_1.SetNext(&ih_2)->SetNext(&ih_3);
	EXPECT_EQ("3", ih_1.Handle(3));
}

TEST(ChainOfResposibility, RequestIsNotHandledByTheLastHandler) {
	// Test the string request handler
	std::string expected_helper_text{""};
	HandlerStringReq ch_1{};
	HandlerStringReq ch_2{};
	HandlerStringReq ch_3{};
	// set the handler chain
	ch_1.SetNext(&ch_2)->SetNext(&ch_3);
	EXPECT_EQ(expected_helper_text, ch_1.Handle({}));

	// Test the int request handler
	HandlerIntReq ih_1{1};
	HandlerIntReq ih_2{2};
	HandlerIntReq ih_3{3};
	// set the handler chain
	ih_1.SetNext(&ih_2)->SetNext(&ih_3);
	EXPECT_EQ("", ih_1.Handle(0));
}
