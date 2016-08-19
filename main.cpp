#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>

/// Get example path
static inline std::string getExamplePath()
{
    std::string filePath(__FILE__);
    return filePath.substr( 0, filePath.length() - std::string("main.cpp").length()) + "/SQLiteCpp/examples/example1";
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::cout << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")" << std::endl;
    std::cout << "SQliteC++ version " << SQLITECPP_VERSION << std::endl;

    /// Example Database
    static const std::string filename_example_db3 = getExamplePath() + "/example.db3";

    // Open a database file in readonly mode
    SQLite::Database    db(filename_example_db3);  // SQLite::OPEN_READONLY
    std::cout << "SQLite database file '" << db.getFilename().c_str() << "' opened successfully\n";

    // Test if the 'test' table exists
    const bool bExists = db.tableExists("test");
    std::cout << "SQLite table 'test' exists=" << bExists << "\n";

    // Get a single value result with an easy to use shortcut
    const std::string value = db.execAndGet("SELECT value FROM test WHERE id=2");
    std::cout << "execAndGet=" << value.c_str() << std::endl;

    // Compile a SQL query, containing one parameter (index 1)
    SQLite::Statement   query(db, "SELECT * FROM test WHERE size > ?");

    // Bind the integer value 6 to the first parameter of the SQL query
    query.bind(1, 6);

    // Loop to execute the query step by step, to get rows of result
    while (query.executeStep())
    {
        // Demonstrate how to get some typed column value
        int         id      = query.getColumn(0);
        const char* value   = query.getColumn(1);
        int         size    = query.getColumn(2);

        std::cout << "row: " << id << ", " << value << ", " << size << std::endl;
    }

    return 0;
}