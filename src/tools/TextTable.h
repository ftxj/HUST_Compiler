#ifndef __TEXTTABLE_H__
#define __TEXTTABLE_H__
#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
#include <string>

class TextTable {
    public:
        enum class Alignment { 
            LEFT, RIGHT 
        }; 
        typedef std::vector<std::string> Row;
        int mutable tableRowLength;
        std::string head;
    private:
        char _horizontal;
        char _vertical;
        char _corner;
        Row _current;
        std::vector<Row> _rows;
        std::vector<unsigned> mutable _width;
        std::map<unsigned, Alignment> mutable _alignment;
    public:
        TextTable( char horizontal = '-', char vertical = '|', char corner = '+' ) :
            _horizontal(horizontal), _vertical(vertical), _corner(corner) {}

        void setAlignment(unsigned i, Alignment alignment) {
            _alignment[i] = alignment;
        }
        
        void setHead(std::string h) {
            head.assign(h);
        }

        Alignment alignment(unsigned i) const { 
            return _alignment[i]; 
        }

        char vertical() const { 
            return _vertical; 
        }

        char horizontal() const { 
            return _horizontal; 
        }

        void add(std::string const & content) {
            _current.push_back(content);
        }

        void endOfRow() {
            _rows.push_back(_current);
            _current.assign(0, "" );
        }

        template <typename Iterator>
        void addRow(Iterator begin, Iterator end) {
            for( auto i = begin; i != end; ++i ) {
                add(*i); 
            }
            endOfRow();
        }

        template <typename Container>
        void addRow(Container const & container ) {
            addRow(container.begin(), container.end());
        }

        std::vector< Row > const & rows() const {
            return _rows;
        }

        void setup() const {
            determineWidths();
            setupAlignment();
        }
        
        std::string header() const {
            std::string result;
            result += _horizontal;
            for(auto width = _width.begin(); width != _width.end(); ++width) {
                result += repeat(*width, _horizontal);
                result += _horizontal;
            }
            return result;
        }
        
        std::string ruler() const {
            std::string result;
            result += _corner;
            for( auto width = _width.begin(); width != _width.end(); ++width) {
                result += repeat(*width, _horizontal);
                result += _corner;
            }
            return result;
        }

        int width(unsigned i) const { 
            return _width[i]; 
        }

    private:
        static std::string repeat( unsigned times, char c ) {
            std::string result;
            for( ;times > 0; --times)
                result += c;

            return result;
        }
        unsigned columns() const {
            return _rows[0].size();
        }

        void determineWidths() const {
            _width.assign(columns(), 0);
            for (auto rowIterator = _rows.begin(); rowIterator != _rows.end(); ++rowIterator) {
                Row const & row = *rowIterator;
                for (unsigned i = 0; i < row.size(); ++i) {
                    _width[i] = _width[i] > row[i].size() ? _width[i] : row[i].size();
                }
            }
            tableRowLength = 0;
            int headLength = head.length();
            for(auto w : _width) {
                tableRowLength += w + 1;
            }
            if(tableRowLength < headLength + 4) {
                _width[_width.size() - 1] += headLength + 4 - tableRowLength + 1;
                tableRowLength += headLength - tableRowLength + 1 + 4;
            }
        }

        void setupAlignment() const {
            for ( unsigned i = 0; i < columns(); ++i ) {
                if ( _alignment.find(i) == _alignment.end()) {
                    _alignment[i] = Alignment::LEFT;
                }
            }
        }
};
std::ostream & operator<<( std::ostream & stream, TextTable const & table );
#endif