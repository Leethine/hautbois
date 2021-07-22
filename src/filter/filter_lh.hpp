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

#include "filter_basic.hpp"

#define NUMTYPE double
#define MAXFILTERSIZE 5
#define PI 3.1415926535898

using namespace std;


class LowPassFilter: public Filter {
/* Low-pass filter class */
public:
    LowPassFilter();
    //bool ApplyFilter();
    bool ApplyFilter(NUMTYPE fs, NUMTYPE fc);
    static vector<NUMTYPE> ApplyFilter(vector<NUMTYPE> d, NUMTYPE fs, NUMTYPE fc);
    static vector<NUMTYPE> ApplyFilter(const NUMTYPE * d, int len, NUMTYPE fs, NUMTYPE fc);
};


class HighPassFilter: public Filter {
/* High-pass filter class */
public:
    HighPassFilter();
    //bool ApplyFilter();
    bool ApplyFilter(NUMTYPE fs, NUMTYPE fc);
    static vector<NUMTYPE> ApplyFilter(vector<NUMTYPE> d, NUMTYPE fs, NUMTYPE fc);
    static vector<NUMTYPE> ApplyFilter(const NUMTYPE * d, int len, NUMTYPE fs, NUMTYPE fc);
};


