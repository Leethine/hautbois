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

#include"filter_lh.hpp"
#include <cmath>
#include <iostream>


using namespace std;


/* Implementing the Low pass filter */
LowPassFilter::LowPassFilter() {};

/*
bool LowPassFilter::ApplyFilter() {
    cout << "LowPassFilter: Abstract method." << endl;
    return false;
}
*/

bool LowPassFilter::ApplyFilter(NUMTYPE fs, NUMTYPE fc) {
/* Apply RC low-pass filter on data samples,
   given time interval dt (fs) and time constant RC (fc) */
    NUMTYPE dt = 1 / fs;
    NUMTYPE RC = 1 / (2 * PI * fc);
    vector<NUMTYPE> newdata (data);
    NUMTYPE alpha = dt / (RC + dt);
    newdata[0] = alpha * data[0];
    
    // cannot handle data shorter than 3 
    int n = length();
    if ( n < 3 )
        return false;
    
    for (int i=1; i < n; i++) {
        newdata[i] = alpha * data[i] + (1 - alpha) * newdata[i-1];
    }
    
    data = newdata;
    return true;
}

vector<NUMTYPE> LowPassFilter::ApplyFilter(vector<NUMTYPE> d, NUMTYPE fs, NUMTYPE fc) {
/* Apply RC low-pass filter on data samples,
   given time interval dt (fs) and time constant RC (fc) */
    NUMTYPE dt = 1 / fs;
    NUMTYPE RC = 1 / (2 * PI * fc);
    vector<NUMTYPE> newdata (d);
    NUMTYPE alpha = dt / (RC + dt);
    newdata[0] = alpha * d[0];
    
    // cannot handle data shorter than 3 
    int n = d.size();
    if ( n < 3 )
        return d;
    
    for (int i=1; i < n; i++) {
        newdata[i] = alpha * d[i] + (1 - alpha) * newdata[i-1];
    }
    
    return newdata;
}

vector<NUMTYPE> LowPassFilter::ApplyFilter(const NUMTYPE * d, int len, NUMTYPE fs, NUMTYPE fc) {
/* Apply RC low-pass filter on data samples,
   given time interval dt (fs) and time constant RC (fc) */
    NUMTYPE dt = 1 / fs;
    NUMTYPE RC = 1 / (2 * PI * fc);
    vector<NUMTYPE> newdata;
    NUMTYPE alpha = dt / (RC + dt);
    newdata.push_back(alpha * d[0]);
    
    // cannot handle data shorter than 3 
    if ( len < 3 ) {
        newdata.push_back(d[1]);
        return newdata;
    }
    
    for (int i=1; i < len; i++) {
        newdata.push_back(alpha * d[i] + (1 - alpha) * newdata[i-1]);
    }
    
    return newdata;
}


/* Implementing the High pass filter */
HighPassFilter::HighPassFilter() {};

/*
bool HighPassFilter::ApplyFilter() {
    cout << "HighPassFilter: Abstract method." << endl;
    return false;
}
*/

bool HighPassFilter::ApplyFilter(NUMTYPE fs, NUMTYPE fc) {
/* Apply RC low-pass filter on data samples,
   given time interval dt (fs) and time constant RC (fc) */
    NUMTYPE dt = 1 / fs;
    NUMTYPE RC = 1 / (2 * PI * fc);
    vector<NUMTYPE> newdata (data);
    NUMTYPE alpha = RC / (RC + dt);
    newdata[0] = data[0];
    
    // cannot handle data shorter than 3 
    int n = length();
    if ( n < 3 )
        return false;
    
    for (int i=1; i < n; i++) {
        newdata[i] = alpha * newdata[i-1] + alpha * (data[i]-data[i-1]);
    }
    
    data = newdata;
    return true;
}

vector<NUMTYPE> HighPassFilter::ApplyFilter(vector<NUMTYPE> d, NUMTYPE fs, NUMTYPE fc) {
/* Apply RC low-pass filter on data samples,
   given time interval dt (fs) and time constant RC (fc) */
    NUMTYPE dt = 1 / fs;
    NUMTYPE RC = 1 / (2 * PI * fc);
    vector<NUMTYPE> newdata (d);
    NUMTYPE alpha = RC / (RC + dt);
    newdata.push_back(d[0]);
    
    // cannot handle data shorter than 3 
    int n = d.size();
    if ( n < 3 )
        return d;
    
    for (int i=1; i < n; i++) {
        newdata.push_back(alpha * newdata[i-1] + alpha * (d[i]-d[i-1]));
    }
    
    return newdata;
}

vector<NUMTYPE> HighPassFilter::ApplyFilter(const NUMTYPE * d, int len, NUMTYPE fs, NUMTYPE fc) {
/* Apply RC low-pass filter on data samples,
   given time interval dt (fs) and time constant RC (fc) */
    NUMTYPE dt = 1 / fs;
    NUMTYPE RC = 1 / (2 * PI * fc);
    vector<NUMTYPE> newdata;
    NUMTYPE alpha = RC / (RC + dt);
    newdata.push_back(d[0]);
    
    // cannot handle data shorter than 3 
    if ( len < 3 ) {
        newdata.push_back(d[1]);
        return newdata;
    }
    
    for (int i=1; i < len; i++) {
        newdata.push_back(alpha * newdata[i-1] + alpha * (d[i]-d[i-1]));
    }
    
    return newdata;
}

