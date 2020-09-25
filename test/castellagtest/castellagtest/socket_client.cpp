#include "pch.h"

#include "SCSocketConnector.h"

TEST(SCSocketConnector, TestSCSocketConnector)
{
	SCSocketConnector connector;
	connector.set_timeout(10, 10, 10);
	ASSERT_EQ(connector.open(SCTEXT("127.0.0.1"), 18081), 0);

	char* send_string = "test data send... echo server will return this string.";
	const int send_size = strlen(send_string);
	ASSERT_EQ(connector.send_data((unsigned char*)send_string, send_size), send_size);
	
	// return message is "ok"
	const int MAX_BUFFER_SIZE = 2;
	unsigned char buffer[MAX_BUFFER_SIZE+1] = {'\0',};
	
	ASSERT_GT(connector.recv_data(buffer, MAX_BUFFER_SIZE), 0);
	
	ASSERT_STREQ((char*)buffer, "ok");
	
	printf("%s", (char*)buffer);
	
	connector.close();
	
	return ;
}