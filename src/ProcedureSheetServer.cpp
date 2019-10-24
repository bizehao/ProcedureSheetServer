// ProcedureSheetServer.cpp: 定义应用程序的入口点。
//

#include "ProcedureSheetServer.h"
#include "asio.hpp"
#include "cinatra.hpp"
#include "ormpp/dbng.hpp"
#include "ormpp/mysql.hpp"
#include <memory>
#include <thread>


struct person {
    int id;
    std::string name;
    int age;
};
REFLECTION(person, id, name, age)

std::string_view getView() {
    char ar[] = "Example";
    return {ar};
}


int main() {
    std::cout << getView() << std::endl;

    person p = { 1, "test1", 2 };
    person p1 = { 2, "test2", 3 };
    person p2 = { 3, "test3", 4 };
    std::vector<person> v{ p1, p2 };

    ormpp::dbng<ormpp::mysql> mysql;
    mysql.connect("127.0.0.1", "root", "bzh960912", "test");
    mysql.create_datatable<person>();

    mysql.insert(p);
    mysql.insert(v);

    mysql.update(p);
    mysql.update(v);

    auto result = mysql.query<person>(); //vector<person>
    for (auto& person : result) {
        std::cout << person.id << " " << person.name << " " << person.age << std::endl;
    }

    mysql.delete_records<person>();

    //transaction
    mysql.begin();
	for (int i = 0; i < 10; ++i) {
		person s = { i, "tom", 19 };
		if (!mysql.insert(s)) {
			mysql.rollback();
			return -1;
		}
	}
	mysql.commit();

	std::thread thread([](){
	    std::cout << "测试" << std::endl;
	});
    thread.join();
}
