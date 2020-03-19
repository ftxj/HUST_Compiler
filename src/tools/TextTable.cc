#include "../tools/TextTable.h"
#include <string>
#include <iostream>
std::ostream & operator<<( std::ostream & stream, TextTable const & table ) {
    table.setup();
    stream << table.header() << "\n";
    stream << table.vertical();
    std::string space;
    for(int i = 0; i < (table.tableRowLength - 1 - table.head.length()) / 2; ++i) {
        space += " ";
    }
    stream << std::setw(table.tableRowLength - 1) << std::left << space + table.head;
    stream << table.vertical();
    stream << "\n";
    stream << table.header() << "\n";
    stream << table.ruler() << "\n";
    for ( auto rowIterator = table.rows().begin(); rowIterator != table.rows().end(); ++ rowIterator ) {
        TextTable::Row const & row = *rowIterator;
        stream << table.vertical();
        for (unsigned i = 0; i < row.size(); ++i) {
            auto alignment = table.alignment(i) == TextTable::Alignment::LEFT ? std::left : std::right;
            stream << std::setw(table.width(i)) << alignment << row[i];
            stream << table.vertical();
        }
        stream << "\n";
        stream << table.ruler() << "\n";
    }
    return stream;
}