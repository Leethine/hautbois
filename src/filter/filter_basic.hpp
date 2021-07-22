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

#include<string>
#include<vector>

#define NUMTYPE double
#define MAXFILTERSIZE 5
#define PI 3.1415926535898

using namespace std;

class Filter {
/* Filter mother class */
public:
    Filter();
    int length();
    bool LoadData(const NUMTYPE * d, int len);
    bool LoadData(const vector<NUMTYPE> d);
    bool FeedData(const NUMTYPE d);
    bool ClearData();
    vector<NUMTYPE> GetData();
    virtual bool ApplyFilter();
    
protected:
    vector<NUMTYPE> data;
};

