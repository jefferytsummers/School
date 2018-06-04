//Author:      Ryan Florida
//Professor:   Dr. Phillips
//Project:     OLA4
//Description: This program uses k-means clustering in order to create a
//             classifer for a given data set.
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <set>
#include <limits>
#include <unordered_map>
#include <cmath>

//For readability.
#define inf std::numeric_limits<long double>::max()

//Ease the tedium of preceding each instance of ifstream with "std::".
using std::ifstream;
using ::sqrt;

//Forward declaration of struct.
struct Data;

//Some useful aliases.
typedef std::vector<double>          dVec;
typedef std::vector<Data>            DVec;
typedef std::vector<DVec*>           DDVec;
typedef std::vector<int>             iVec;
typedef std::unordered_map<int, int> map;
typedef std::set<int>::iterator      setIt;

//Struct to hold data from file.
struct Data
{
    dVec location; //Store location of data record in N-space.
    int  label;    //Label associated with data object.

    //Overload comparison operator.
    bool operator ==(const Data& lhs) const
    {
        int size = location.size();
        for(int i = 0; i < size; ++i)
            if(location[i] != lhs.location[i])
                return false;
        return true;
    }
};

//1:   Populates vector of data records and chooses initial centroids.
void        GeneratePoints(DVec&, ifstream&, DVec&, DDVec&, const int&,
                           const int&, iVec&);
//2:   Performs the clustering.
void        Cluster(const DVec&, DDVec&, const DVec&);
//3:   Calculates new centroid vectors based upon cluster members.
void        CalculateCentroids(DVec&, DDVec&, const int&, const int&);
//4:   Labels centroids according to majority vote of cluster member labels.
void        LabelCentroids(DVec&, const DDVec&, const int&, const iVec&);
//5:   Chooses ideal labels for test data according to cluster membership.
void        ClassifyTestData(ifstream&, const DVec&, const int&);
//1.1: Checks if a given label has already been identified.
bool        IsIn(const int&, const iVec&);
//3.1: Returns the generalized Euclidean distance between two data vectors.
long double Distance(const Data&, const Data&);


//0: Main.
int main(int argc, char* argv[])
{
    //Seed random number generation.
    std::srand(atoi(argv[1]));

    int      k        = atoi(argv[2]), //Number of clusters.
             features = atoi(argv[3]); //Number of features.
    ifstream train(argv[4]),           //File containing training data.
             test(argv[5]);            //File containing testing data.
    DVec     points,                   //Vector to hold all input data objects.
             centroids;                //Vector to hold each centroid.
    DDVec    clusters;                 //Vector to hold all clusters.
    bool     different = 1;            //Bool to let us know about clusters.
    iVec     labels;                   //Vector containing all potential lables.

    //Reserve appropriate amount of storage.
    clusters.reserve(k);
    centroids.reserve(k);

    //Collect data from input file and choose k random objects as centroids.
    GeneratePoints(points, train, centroids, clusters, features, k, labels);

    //Priming stage of clusters.
    Cluster(centroids, clusters, points);

    //This loop will proceed until there is no swapping of cluster members.
    while(different)
    {
        different = 0;
        //Remember previous centroids.
        DVec old_centroids = centroids;
        //Calculate new centroids based on cluster members.
        CalculateCentroids(centroids, clusters, k, features);
        //Check to see if there changes to at least one centroid.
        if(centroids != old_centroids)
            different = 1;
        //Cluster around new centroids.
        Cluster(centroids, clusters, points);
    }

    //Label the centroids based on majority vote amongst members.
    LabelCentroids(centroids, clusters, k, labels);

    //Determine most appropriate labels for test data members.
    ClassifyTestData(test, centroids, features);

    return 0;
}

//******************************************************************************
//1: Populates vector of data records and chooses initial centroids.
void GeneratePoints(DVec& points, ifstream& train, DVec& centroids,
                    DDVec& clusters, const int& features, const int& k,
                    iVec& labels)
{
    int           size;         //Hold size of points vector.
    std::set<int> uniquePoints; //Holds indices of random initial clusters.

    //Read in training data and populate the points vector with the data.
    do
    {
        Data record;
        for(int i = 0; i < features; ++i)
        {
            double point;
            train >> point;
            record.location.push_back(point);
        }
        int l;
        train >> l;
        if(!IsIn(l, labels)) //Test if a label has been seen or not.
            labels.push_back(l);
        record.label = l;
        if(!train)
            break;
        points.push_back(record);
    }while(true);

    size = points.size();

    //Generate random indices.
    while(uniquePoints.size() != k)
        uniquePoints.insert(std::rand()%size);

    //Randomize initial centroids and initialize corresponding clusters.
    for(setIt i = uniquePoints.begin(); i != uniquePoints.end(); ++i)
    {
        centroids.push_back(points[*i]);
        clusters.push_back(new DVec);
    }

    return;
}

//******************************************************************************
//2: Performs the clustering.
void Cluster(const DVec& centroids, DDVec& clusters, const DVec& points)
{
    int pSize = points.size(),    //Holds size of points vector.
        cSize = centroids.size(), //Holds size of centroids vector.
        idealCluster = 0;         //Stores value of most ideal cluster.

    //Clear previous clusters.
    for(int i = 0; i < cSize; ++i)
        clusters[i]->clear();

    //Determine cluster membership based upon Euclidean distance from centroid.
    for(int p = 0; p < pSize; ++p)
    {
        long double minDist = inf;
        for(int c = 0; c < cSize; ++c)
        {
            long double check_dist = Distance(points[p], centroids[c]);
            if(check_dist < minDist)
            {
                minDist = check_dist;
                idealCluster = c;
            }
        }
        clusters[idealCluster]->push_back(points[p]);
    }

    return;
}

//******************************************************************************
//3: Calculates new centroid vectors based upon cluster members.
void CalculateCentroids(DVec& centroids, DDVec& clusters, const int& k,
                        const int& features)
{
    dVec   sums; //Vector to hold sums along each feature dimension.
    double sum;  //Variable to store running sums.

    //Calculate the average value accross each dimension and update centroid.
    for(int c1 = 0; c1 < k; ++c1)
    {
        sums.clear();
        //Average calculation.
        for(int f = 0; f < features; ++f)
        {
            int divisor;
                sum = 0.0;
                divisor = clusters[c1]->size();
                //Sum across individual feature dimension.
                for(int i = 0; i < divisor; ++i)
                    sum += (*clusters[c1])[i].location[f];
                if(divisor != 0)
                    sum /= divisor;
                sums.push_back(sum);
        }
        centroids[c1].location = sums;
    }

    return;
}

//******************************************************************************
//4: Labels centroids according to majority vote of cluster member labels
void LabelCentroids(DVec& centroids, const DDVec& clusters, const int& k,
                    const iVec& labels)
{
    //Find most frequently occurring label in a cluster and assign to centroid.
    for(int c = 0; c < k; ++c)
    {
        map count;
        int max   = 0,
            lSize = labels.size(),
            cSize = clusters[c]->size(),
            most_common_label;
        //Initialize label counts to 0.
        for(int i =0; i < lSize; ++i)
            count[labels[i]] = 0;
        //Increment label counts appropriately.
        for(int p = 0; p < cSize; ++p)
            ++count[(*clusters[c])[p].label];
        //Search for and store most frequently occuring label.
        for(int i = 0; i < lSize; ++i)
            if(count[labels[i]] > max)
            {
                max               = count[labels[i]];
                most_common_label = labels[i];
            }
        centroids[c].label = most_common_label;
    }
}

//******************************************************************************
//5: Chooses ideal labels for test data according to cluster membership.
void ClassifyTestData(ifstream& test, const DVec& centroids,
                      const int& features)
{
    DVec     testPoints;               //Vector to store test opints.
    int      count = 0,                //Stores number of correct labelings.
             pSize,                    //Stores size of testPoints vector.
             cSize = centroids.size(), //Stores size of centroids vector.
             idealCluster = 0;         //Stores value of ideal cluster.

    //Read in testing data.
    do
    {
        Data record;
        for(int i = 0; i < features; ++i)
        {
            double point;
            test >> point;
            record.location.push_back(point);
        }
        int l;
        test >> l;
        record.label = l;
        if(!test)
            break;
        testPoints.push_back(record);
    }while(true);

    pSize = testPoints.size();

    //Find ideal cluster membership.
    for(int p = 0; p < pSize; ++p)
    {
        double minDist = inf;
        for(int c = 0; c < cSize; ++c)
        {
            long double check_dist = Distance(testPoints[p], centroids[c]);
            if(check_dist < minDist)
            {
                minDist = check_dist;
                idealCluster = c;
            }
        }
        if(centroids[idealCluster].label == testPoints[p].label)
            ++count;
    }

    //Print number of correctly classified test points.
    std::cout << count << '\n';

    return;
}

//******************************************************************************
//1.1: Checks if a given label has already been identified.
bool IsIn(const int& label, const iVec& labels)
{
    int size = labels.size(); //Stores size of label vector.

    //Determine if a label has been seen previously.
    for(int i = 0; i < size; ++i)
        if(label == labels[i])
            return true;
    return false;
}

//******************************************************************************
//3.1: Returns the generalized Euclidean distance between two data vectors.
long double Distance(const Data& vec1, const Data& vec2)
{
    int         dim = vec1.location.size(); //Stores dimension of feature space.
    long double sum = 0.0;                  //Stores running sum.

    //Calculate sum of squared differences.
    for(int i = 0; i < dim; ++i)
        sum += (vec1.location[i] - vec2.location[i])
                *(vec1.location[i] - vec2.location[i]);

    //Return square root of sum of squared differences.
    return sqrt(sum);
}