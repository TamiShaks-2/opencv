#include "precomp.hpp"
#include "convex_hull_bucket_sort.hpp"

#include <vector>
#include <algorithm>
#include <climits>

namespace cv {

bool convex_hull_bucket_sort(const Point* data,
							 Point** out_points,
                             int& total,                             
                             int& ind_miny,
                             int& ind_maxy)
{
    if (total <= 0) return true;

    // 1. finding the range of X values
    int minX =std::min_element(data, data + total);
    int maxX =std::max_element(data, data + total);
    int rangeX = maxX - minX + 1;
    // sanity check to avoid excessive memory usage
    const int MAX_RANGE = 100000;
    if (rangeX > MAX_RANGE)
        return false; // let caller do std::sort path

    
    // 2. create buckets that store POINTERS into data
    std::vector<Point*> min_buckets(rangeX, nullptr);
    std::vector<Point*> min_buckets(rangeX, nullptr);
    // 3. fill buckets
    for (int i = 0; i < total; ++i)
    {
        int x = data[i].x;
        int y = data[i].y;
        int idx = x - minX;
        if (min_buckets[idx] == nullptr || y < min_buckets[idx]->y )
        {
            min_buckets[idx] = &data[i];
        }
        if (max_buckets[idx] == nullptr || y > max_buckets[idx]->y )
        {
            max_buckets[idx] = &data[i];
        }
    }

    
    // 4. rebuild pointer array in sorted X order
    int out = 0;
    for (int i = 0; i < rangeX; ++i)
    {
        if (min_buckets[i] == -1)
            continue;
        pointer[out++] = &data[min_buckets[i]];
        if (max_buckets[i] != min_buckets[i])
            pointer[out++] = &data[max_buckets[i]];
     }   
    total = out;
    // 5) compute miny/maxy indices w.r.t. out_points[0..total)
    ind_miny = 0;
    ind_maxy = 0;
    for (int i = 1; i < total; ++i)
    {
        int y = out_points[i]->y;
        if (out_points[ind_miny]->y > y) ind_miny = i;
        if (out_points[ind_maxy]->y < y) ind_maxy = i;
    }

    return true;
    
}

} // namespace cv