/*

  This file is part of the HAUTBOIS project, which is released under
  the GNU General Public License. You should have received a copy of 
  the GNU General Public License along with Hautbois.  
  If not, see <http://www.gnu.org/licenses/>.

*/

/* filter.hpp
 * Implemented commonly-used filters
 * 
 */

#include"filter_basic.hpp"
#include <cmath>
#include <iostream>


using namespace std;

/* Implementing the template Filter class  */
Filter::Filter() {};

int Filter::length() {
    return data.size();
}

bool Filter::LoadData(const NUMTYPE * d, int len) {
/* Load data from array */
    if ( data.size() != 0 ) { 
        return false;
    }
    else {
        for (int i=0; i < len; i++) {
            data.push_back(d[i]);
        }
        return true;
    }
}

bool Filter::LoadData(const vector<NUMTYPE> d) {
/* Load data from vector */
    if ( data.size() != 0 ) { 
        return false;
    }
    else {
        data = d;
        return true;
    }
}

bool Filter::FeedData(const NUMTYPE d) {
/* Feed one single value in the data vector */
    if ( data.size() != 0 ) { 
        return false;
    }
    else {
        data.push_back(d);
        return true;
    }
}

bool Filter::ClearData() {
    if ( data.size() != 0 ) { 
        return false;
    }
    else {
        data.clear();
        return true;
    }

}

vector<NUMTYPE> Filter::GetData() {
    return data;
}

//bool Filter::ApplyFilter() = 0;
bool Filter::ApplyFilter() { return false; }


