//Author:      Ryan Florida
//Project:     OLA3
//Professor:   Dr. Phillips
//Description: This program is an implementation of the ID3 classification
//             algorithm.
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <unordered_map>
#include <vector>
#include <cstdlib>

using std::string;
using std::ifstream;
using std::vector;
using std::unordered_map;
using std::cout;
using ::log2;
using std::rand;

//Forward struct declarations.
struct Record;
struct Node;

//Convenient aliases.
typedef vector<double>::iterator                      d_iter;
typedef vector<Record*>::iterator                     r_iter;
typedef vector<int>::iterator                         i_iter;
typedef vector<Record*>                               Rec;
typedef vector<double>                                Dec;
typedef unordered_map<int, vector<double> >           Map;
typedef unordered_map<int, int>                       iMap;
typedef unordered_map<int, vector<double> >::iterator m_iter;

//Struct to hold training/testing data.
struct Record
{
    int    label;     //Proper label.
    Dec    features;  //Feature vector.
    double pivot;     //Use this to store best split point.
    bool   left;      //True => left; False => right

    //Constructor that accepts labels and features.
    Record(int l, vector<double> f)
    :label(l), pivot(0.0), left(0)
    {
        for(d_iter it = f.begin(); it != f.end(); ++it)
            features.push_back(*it); 
    }
};

//Struct that comprises the nodes of our tree.
struct Node
{
    int    label,   //Node label.
           feature, //Feature to compare.
           dir;     //1 => left, 0 => right
    double value;   //Node value.
    Node   *left,   //Left child pointer.
           *right;  //Right child pointer.
    bool   leaf;

    //Constructors.
    Node()
    :label(-1), left(NULL), right(NULL), feature(-1), leaf(1), dir(0)
    {}
    Node(int l)
    :label(l), value(0.0),left(NULL), right(NULL), feature(-1), leaf(1), dir(0)
    {}
    Node(int l, double v)
    :label(l), value(v),left(NULL), right(NULL), feature(-1), leaf(1), dir(0)
    {}
    Node(int l, double v, int f, int d)
    :label(l), value(v),left(NULL), right(NULL), feature(f), leaf(1), dir(d)
    {}
    Node(double v)
    :label(-1), value(v),left(NULL), right(NULL), feature(-1), leaf(1), dir(0)
    {}

    //Add left child to current node.
    void AddLeftChild(Node* child)
    {
        if(left == NULL)
        {
            left = child;
            return;
        }
        if(child->value > value)
            left->AddRightChild(child);
        else
            left->AddLeftChild(child);
    }
    //Add right child to current node.
    void AddRightChild(Node* child)
    {
        if(right == NULL)
        {
            right = child;
            return;
        }
        if(child->value > value)
            right->AddRightChild(child);
        else
            right->AddLeftChild(child);
    }
};

//Class that comprises our tree; make ideal connections between Node objects.
class DecisionTree
{
  public:
    //Constructor.
    DecisionTree()
    :root(NULL)
    {}

    //Calculate information.
    static double CalculateInformation(Rec& records)
    {
        iMap   labels;
        double size = records.size();
        for(r_iter r = records.begin(); r != records.end(); ++r)
        {
            iMap::iterator it = labels.find((*r)->label);
            if(it != labels.end())
                ++labels[(*r)->label];
            else
                labels[(*r)->label] = 1;
        }
        double information = 0.0;
        for(iMap::iterator i = labels.begin(); i != labels.end(); ++i)
            information -= (i->second/size)*log2(i->second/size);

        return information;
    }

    //#########################################################################
    //Quick sort to sort records by feature.
    static void QuickSort(Rec& records, int& feature, int low, int high)
    {
        if (low < high)
        {
            int partition = Partition(records, feature, low, high);
            QuickSort(records, feature, low, partition - 1);
            QuickSort(records, feature, partition + 1, high);
        }

        return;
    }

    //Partition portion of quick sort.
    static int Partition(Rec& records, int& feature, int low, int high)
    {
        double pivot = records[high]->features[feature];    // pivot
        int        i = (low - 1);  // Index of smaller element
     
        for (int j = low; j <= high - 1; ++j)
            if (records[j]->features[feature] <= pivot)
            {
                 ++i;    // increment index of smaller element
                 Swap(records, i, j);
            }
        Swap(records, i + 1, high);
        return (i + 1);
    }

    //Swap portion of quick sort.
    static void Swap(Rec& records, int i, int j)
    {
        Record* temp = records[i];
        records[i]   = records[j];
        records[j]   = temp;
        return;
    }
    //#########################################################################
    //Recursively construct the decision tree from the given training data.
    void Train(Rec records, int features, vector<int> labels, int attribute = -1)
    {
        //If records vector is empty, return.
        if(records.size() == 0)
            return;
        r_iter r1 = records.begin() + 1,
               r2 = records.begin();

        //Check for homogeneity of labels in a record.
        bool homogeneous1;
        while(r1 != records.end())
        {
            homogeneous1 = (*r1)->label == (*r2)->label;
            if(!homogeneous1)
                break;
            ++r1;
            ++r2;
        }

        //Check for homogeneity of feature values across a record.
        bool homogeneous2;
        r1 = records.begin() + 1;
        r2 = records.begin();
        while(attribute >= 0 && r1 != records.end())
        {
            homogeneous2 = (*r1)->features[attribute] == (*r2)->features[attribute];
            if(!homogeneous2)
                break;
            ++r1;
            ++r2;
        }
        //If there is homogenity across a given feature, identify most likely label.
        int mostFrequentLabel;
        if(homogeneous2)
            mostFrequentLabel = FindMostFrequentLabel(records, labels);

        //If the record only consists of one element or the records are
        //homogeneous in either labels or feature values, then construct a
        //node.
        if(records.size() == 1 || homogeneous1 || homogeneous2)
        {
            if(homogeneous2)
            {
                Node* newNode =  new Node(mostFrequentLabel, records[0]->pivot, attribute, records[0]->left);
                GenerateNode(newNode);
            }
            else
            {
                Node* newNode = new Node(records[0]->label, records[0]->pivot, attribute, records[0]->left);
                GenerateNode(newNode);
            }
            return;
        }

        //Calculate information.
        double information = CalculateInformation(records),
               bestSplit;
        Map    splits;
        Rec    left,
               right;

        //Determine split points.
        for(int i = 0; i < features; ++i)
        {
            QuickSort(records, i, 0, records.size() - 1);
            DetermineSplitPoints(records, i, splits);
        }

        //Find best split point.
        FindBestSplit(information, records, splits, left, right, labels, attribute, bestSplit);

        //Train on left of split.
        Train(left, features, labels, attribute);

        //Train on right of split.
        Train(right, features, labels, attribute);
    }

    //Determine the potential split points.
    static void DetermineSplitPoints(Rec records, int feature, Map &splits)
    {
        r_iter r1 = records.begin() + 1,
               r2 = records.begin();
        while(r1 != records.end())
        {
            if((*r1)->features[feature] != (*r2)->features[feature])
                splits[feature].push_back(((*r1)->features[feature] + (*r2)->features[feature])/2);
            ++r1;
            ++r2;
        }
    }

    //Identify best split to make (pick split that maximizes information gain).
    static void FindBestSplit(double information, Rec records, Map splits, Rec& left, Rec& right, vector<int> labels, int& attribute, double& bestSplit)
    {
        double max_gain = 0.0;
        //Calculate gain per split.
        for(m_iter m = splits.begin(); m != splits.end(); ++m)
        {
            double litmus = CalculateGain(information, records, m->first, m->second, labels);
            if(litmus > max_gain)
                max_gain = litmus;
        }
        //Find the pivot value that maximizes the gain.
        for(m_iter m = splits.begin(); m != splits.end(); ++m)
            if(max_gain == CalculateGain(information, records, m->first, m->second, labels))
            {
                attribute = m->first;
                bestSplit = FindPivot(information, records, attribute, m->second, max_gain, labels);
                break;
            }

        //Partition record into two subsets: one with all values less than the
        //best split, and the other with all values greater than the split.
        for(r_iter r = records.begin(); r != records.end(); ++r)
        {
            if((*r)->features[attribute] < bestSplit)
            {
                (*r)->left = 1;
                left.push_back(*r);
            }
            else
            {
                (*r)->left = 0;
                right.push_back(*r);
            }
            (*r)->pivot = bestSplit;
        }
    }

    //Calculate the gain.
    static double CalculateGain(double information, Rec records, int feature, Dec potentialSplits, vector<int> labels)
    {
        QuickSort(records, feature, 0, records.size() - 1);
        double max_gain = 0.0;
        int    size     = records.size();

        for(d_iter d = potentialSplits.begin(); d != potentialSplits.end(); ++d)
        {
            //Store conditional probabilities.
            unordered_map<int, double> lessConditionals;
            unordered_map<int, double> moreConditionals;
            for(int i = 0; i < labels.size(); ++i)
            {
                lessConditionals[i] = 0.0;
                moreConditionals[i] = 0.0;
            }
            int count = 0;
            r_iter r = records.begin();

            while(r != records.end() && (*r)->features[feature] < *d)
            {
                ++lessConditionals[(*r)->label];
                ++count;
                ++r;
            }
            while(r != records.end() && (*r)->features[feature] > *d)
            {
                ++moreConditionals[(*r)->label];
                ++r;
            }

            for(int i = 0; i < labels.size(); ++i)
            {
                lessConditionals[i] /= count;
                moreConditionals[i] /= (size - count);
            }

            double lessProb = (double) count/size,
                   moreProb = (double) (size - count)/size;

            //Calculate weighted expectation value.
            double expectation = 0.0;
            for(int i = 0; i < labels.size(); ++i)
            {
                expectation -= (lessConditionals[i] != 0.0)
                             ? lessProb*(lessConditionals[i]*log2(lessConditionals[i]))
                             : 0.0;
                expectation -= (moreConditionals[i] != 0.0)
                             ? moreProb*(moreConditionals[i]*log2(moreConditionals[i]))
                             : 0.0;
            }

            //Calculate gain.
            double current_gain = information - expectation;
            if(current_gain > max_gain)
                max_gain = current_gain;
        }

        return max_gain;
    }

    //Find pivot (split) that corresonds to the maximal information gain.
    //(Almost same as above, just ends earlier).
    static double FindPivot(double information, Rec records, int feature, Dec potentialSplits, double gain, vector<int> labels)
    {
        QuickSort(records, feature, 0, records.size() - 1);
        int size = records.size();
        for(d_iter d = potentialSplits.begin(); d != potentialSplits.end(); ++d)
        {
            unordered_map<int, double> lessConditionals;
            unordered_map<int, double> moreConditionals;
            for(int i = 0; i < labels.size(); ++i)
            {
                lessConditionals[i] = 0.0;
                moreConditionals[i] = 0.0;
            }
            int count = 0;
            r_iter r = records.begin();

            while(r != records.end() && (*r)->features[feature] < *d)
            {
                ++lessConditionals[(*r)->label];
                ++count;
                ++r;
            }
            while(r != records.end() && (*r)->features[feature] > *d)
            {
                ++moreConditionals[(*r)->label];
                ++r;
            }
            for(int i = 0; i < labels.size(); ++i)
            {
                lessConditionals[i] /= count;
                moreConditionals[i] /= (size - count);
            }

            double lessProb = (double) count/size,
                   moreProb = (double) (size - count)/size,
                   expectation = 0.0;
            for(int i = 0; i < labels.size(); ++i)
            {
                expectation -= (lessConditionals[i] != 0.0)
                             ? lessProb*(lessConditionals[i]*log2(lessConditionals[i]))
                             : 0.0;
                expectation -= (moreConditionals[i] != 0.0)
                             ? moreProb*(moreConditionals[i]*log2(moreConditionals[i]))
                             : 0.0;
            }

            double current_gain = information - expectation;
            if(current_gain == gain)
                return *d;
        }

        return 0.0;
    }

    //Identify most likely label in a given record.
    int FindMostFrequentLabel(Rec& records, vector<int>& labels)
    {
        unordered_map<int, int> count;
        for(i_iter i = labels.begin(); i != labels.end(); ++i)
            count[*i] = 0;
        for(r_iter r = records.begin(); r != records.end(); ++r)
            ++count[(*r)->label];
        int max = 0,
            maxLabel = 0;
        for(i_iter i = labels.begin(); i != labels.end(); ++i)
            if(count[*i] > max)
            {
                max      = count[*i];
                maxLabel = *i;
            }
        return maxLabel;
    }

    //Generate a tree node.
    void GenerateNode(Node* n)
    {
        if(root == NULL)
            root = n;
        else if(!(n->dir))
            root->AddLeftChild(n);
        else
            root->AddRightChild(n);
    }

    //Mark all interior (non-leaf nodes) as not leaf nodes.
    void PrepNodes()
    {
        Node* n = root;
        TraverseTree(n);
    }

    //Traverse tree.
    void TraverseTree(Node* n)
    {
        if(n == NULL)
            return;
        if(!(n->left == NULL && n->right == NULL))
            n->leaf = 0;
        TraverseTree(n->left);
        TraverseTree(n->right);

    }

    //Classify testing data.
    void Classify(Rec testSubjects)
    {
        //Make sure all interior nodes are not marked as leaves.
        PrepNodes();

        //Count number of correctly classified nodes.
        int correct = 0;
        for(r_iter r = testSubjects.begin(); r != testSubjects.end(); ++r)
            if((*r)->label == AssignLabel(*r))
                ++correct;
        cout << correct << '\n';
    }

    //Assign a label to a test subject.
    int AssignLabel(Record* rec)
    {
        Node *n     = root,
             *trail = n;
        while(n != NULL)
        {
            n->label = rec->label;
            if(rec->features[n->feature] <= n->value && n->left != NULL)
            {
                trail = n;
                n     = n->left;
            }
            else if(rec->features[n->feature] <= n->value && n->leaf)
                return n->label;
            else if(rec->features[n->feature] > n->value && n->leaf)
                return (n->label + rand())%3;
            else
            {
                trail = n;
                n     = n->right;
            }
        }
        return trail->label;
    }

  private:
    //Root of tree.
    Node* root;
};

//1: Determine if item is already in input vector.
bool IsIn(int, vector<int>);                                            //DONE.

//0: Main
int main(int argc, char* argv[])                                        //DONE.
{
    int          features = atoi(argv[1]), //Store number of features.
                 label,                    //Store training labels.
                 test_label;               //Store test labels.
    ifstream     train(argv[2]);           //Training data file object.
    ifstream     test(argv[3]);            //Testing data file object.
    Dec          feat,                     //Training feature vector.
                 test_feat;                //Testing feature vector.
    Rec          records,                  //Stores training records.
                 testSubjects;             //Store test records.
    vector<int>  labels;                   //Store labels.
    DecisionTree Tree;                     //Create a DecisionTree object.

    //Resize feature vectors.
    feat.resize(features);                   
    test_feat.resize(features);         

    //Populate training data vector.
    do
    {
        for(int i = 0; i < features; ++i)
            train >> feat[i];

        train >> label;
        if(train.eof())
            break;

        //Keep track of labels.
        if(!IsIn(label, labels))
            labels.push_back(label);

        Record* newNode = new Record(label, feat);
        records.push_back(newNode);

    }while(true);

    //Populate testing data vector.
    do
    {
        for(int i = 0; i < features; ++i)
            test >> test_feat[i];

        test >> test_label;
        if(test.eof())
            break;

        Record* newNode = new Record(test_label, test_feat);
        testSubjects.push_back(newNode);
    }while(true);

    //Train the tree with the training data.
    Tree.Train(records, features, labels);

    //Classify test data.
    Tree.Classify(testSubjects);

    return 0;
}

//*****************************************************************************
//1: Determine if item is already in input vector.
bool IsIn(int l, vector<int> labels)
{
    for(i_iter i = labels.begin(); i != labels.end(); ++i)
        if(l == *i)
            return true;
    return false;
}