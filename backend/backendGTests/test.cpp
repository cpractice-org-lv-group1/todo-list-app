#include "pch.h"
#include"../backend/config.h"
#include "../backend//Users.h"

TEST(Config, StringDatetimeCorrect) {

	std::string stime(getCurrentTime());

    ASSERT_GT(stime , "2022-06-30 22:34:00.000");
}

TEST(Config, StringDatetimeIncorrect) {

	std::string stime(getCurrentTime());

	ASSERT_LE(stime, "2023-06-30 22:34:00.000");
}

TEST(Config, CheckConvertToWchar) {
	std::wstring function_str(GetWCharFromString("something"));

	const char* text = "something";
	std::string t(text);
	std::wstring a(t.begin(), t.end());

	EXPECT_EQ(a, function_str);
}

TEST(Config, LocalTime_xp) {
	auto tm = localtime_xp(time(0));

	EXPECT_EQ(tm.tm_year, 122);
	EXPECT_EQ(tm.tm_mon, 6);
}

TEST(JSON, JSONformater) {
	std::string strjson = "{\"userBithday\":\"2003-09-18\",\"userID\":" + std::to_string(20) + ","+
		"\"userMail\":\"sofia.grechanyu2@gmail.com\","
		+"\"userNameArr\":\"sofia\","+
		"\"userPassword\":\"12345678\","+
		"\"userPoints\":\"0\","+
		"\"userRank\":\"Novice\"," + "\"userSurnameArr\":\"grech\"}";

	auto myJSON = nlohmann::json{ {"userID", 20},
								  {"userNameArr", "sofia"},
								  {"userSurnameArr", "grech"},
								  {"userBithday", "2003-09-18"},
								  {"userMail", "sofia.grechanyu2@gmail.com"},
								  {"userPassword", "12345678"},
								  {"userPoints", "0"},
								  {"userRank", "Novice"}};
	std::string fromobj = myJSON.dump();

	EXPECT_EQ(strjson,fromobj);
}

