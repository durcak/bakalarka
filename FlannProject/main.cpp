#include <iostream>
#include <flann/flann.hpp>
//#include <flann/io/hdf5.h>

//using namespace std;
using namespace flann;

float* read_points(const char* filename, int rows, int cols)
{
    float* data = NULL;
    float *p;
    FILE* fin;

    fin = fopen(filename,"r");
    if (!fin) {
        printf("Cannot open input file.\n");
        exit(1);
    }

    data = (float*) malloc(rows*cols*sizeof(float));

    //data = (float*) malloc(rows*cols*sizeof(float));
    //data = (float*) malloc(16016000000);
    //data = new(std::nothrow)float[rows*cols];
    //data = new(std::nothrow)float[1023*1023*1023*1000];
    if (!data) {
        printf("Cannot allocate memory.\n");
        exit(1);
    }
    else
        std::cout << "alokacia sa podarila";

    //free(data);

    p = data;

    for (int i = 0; i<rows; ++i)
    {
       // if(i < 10) {
            //std::cout << i+1 << ". ";
        char mystring [62];
        fgets(mystring,60,fin);
             // std::cout << mystring << std::endl;
       // }
        for (int j = 0; j<cols; ++j)
        {
            fscanf(fin, "%g ", p);
            //if(i < 10 && j < 5)
               // std::cout << *p << " ";
            p++;
        }
        //if(i < 10)
            //std::cout << std::endl;
    }

    fclose(fin);

    return data;
}


void write_results(const char* filename, int *data, int rows, int cols)
{
    FILE* fout;
    int* p;
    int i,j;

    fout = fopen(filename,"w");
    if (!fout) {
        printf("Cannot open output file.\n");
        exit(1);
    }

    p = data;
    for (i=0;i<rows;++i) {
        for (j=0;j<cols;++j) {
            fprintf(fout,"%d ",*p);
            p++;
        }
        fprintf(fout,"\n");
    }
    fclose(fout);
}


void write_results_float(const char* filename, float *data, int rows, int cols)
{
    FILE* fout;
    float* p;
    int i,j;

    fout = fopen(filename,"w");
    if (!fout) {
        printf("Cannot open output file.\n");
        exit(1);
    }

    p = data;
    for (i=0;i<rows;++i) {
        for (j=0;j<cols;++j) {
            fprintf(fout,"%d ",*p);
            p++;
        }
        fprintf(fout,"\n");
    }
    fclose(fout);
}

int main()
{
    int nn = 2;
    int rows = 100000;
    int cols = 40000;
    int t_rows = 1000;

    //std::cout << memory() << std::endl;

    float* dataset2 = read_points("profi-neuralnet-100K.data", rows, cols);
    std::cout << "Dataset nacitany" << std::endl;

    float* query2 = read_points("profi-neuralnet-1000-query.data", t_rows, cols);
    std::cout << "Qeury nacitany" << std::endl;

    //float* dataset2 = read_points("vector-L2-dim3-100000.data", rows, cols);
    //float* query2 = read_points("queryset-dim32-100.data", t_rows, cols);



    Matrix<float> dataset(dataset2, rows, cols);
    Matrix<float> query(query2, t_rows, cols);

    //load_from_file(dataset, "dataset.hdf5", "dataset");
    //load_from_file(query, "dataset.hdf5", "query");

    Matrix<int> indices(new int[query.rows*nn], query.rows, nn);
    Matrix<float> dists(new float[query.rows*nn], query.rows, nn);

    // construct an randomized kd-tree index using 4 kd-trees
    Index<L2<float> > index(dataset, flann::KDTreeIndexParams(4));
    index.buildIndex();
    std::cout << "Index postaveny" << std::endl;

    // do a knn search, using 128 checks
    index.knnSearch(query, indices, dists, nn, flann::SearchParams(128));

    //flann::save_to_file(indices,"result.hdf5","result");
    write_results("results2.data",indices.ptr(), t_rows, nn);
    write_results_float("ulozeneQuery.data",dists.ptr(), t_rows, nn);

    //index.save("index.dat");
    std::cout << *index.getPoint(0) << " " << *(index.getPoint(0)+1) << std::endl;

    free(dataset2);
    free(query2);
    //delete[] dataset.ptr();
    //delete[] query.ptr();
    delete[] indices.ptr();
    delete[] dists.ptr();

}


