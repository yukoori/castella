#include "pch.h"

#include "SCSharedMemory.h"

struct shared_data {
	char	name[32];
	char	address[256];
};

TEST(SCSharedMemory, TestSCSharedMemory)
{
	SCSharedMemory memory;
	ASSERT_EQ(memory.open("test_shared_memory", sizeof(shared_data) * 10), 0);

	shared_data* pData = (shared_data*) memory.malloc();
//	ASSERT_NE(pData, 0);

	strcpy_s(pData->name, "name1");
	strcpy_s(pData->address, "address1");

	memory.close();

	SCSharedMemory memory1;
	ASSERT_EQ(memory1.open("test_shared_memory", sizeof(shared_data) * 10), 0);

	shared_data* pData1 = (shared_data*)memory1.malloc();
//	ASSERT_NE(pData1, 0);

	ASSERT_STREQ(pData1->name, "name1");
	ASSERT_STREQ(pData1->address, "address1");

	memory1.close();
}