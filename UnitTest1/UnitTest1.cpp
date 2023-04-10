#include "pch.h"
#include "CppUnitTest.h"
#include "../desk_lab7/desk_lab7.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
string Degree();
string isolated();
namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			string fname = "test_graph.txt";
			ofstream file(fname);
			file << "4 4\n1 2\n1 3\n2 3\n3 4\n";
			file.close();
			initGraph(fname);
			Assert::AreEqual(4, vertices);
			Assert::AreEqual(4, edges);
		}

		TEST_METHOD(TestMethod2)
		{
			string result = Degree();
			// перевіряємо, чи результат не порожній рядок
			Assert::IsFalse(result.empty());
			// перевіряємо, чи результат містить певний текст
			Assert::IsTrue(result.find("| V | v-stupeni | poza-stupenem |") != string::npos);
			Assert::IsTrue(result.find("| V1|") != string::npos);
			Assert::IsTrue(result.find("| V2|") != string::npos);
			Assert::IsTrue(result.find("| V3|") != string::npos);
			Assert::IsTrue(result.find("| V4|") != string::npos);
		}
		TEST_METHOD(TestMethod3)
		{
			string result = isolated();
			// перевіряємо, чи результат не порожній рядок
			Assert::IsFalse(result.empty());
			// перевіряємо, чи результат містить певний текст
			Assert::IsTrue(result.find("| Izolovani vershyny| Vysyachi vershyny|") != string::npos);
			Assert::IsTrue(result.find("| v0                |               v0 |") != string::npos);
			Assert::IsTrue(result.find("| v1                |               v1 |") != string::npos);
			Assert::IsTrue(result.find("| v2                |               v2 |") != string::npos);
		}
	};
}
