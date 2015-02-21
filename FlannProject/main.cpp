#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <flann/flann.hpp>
#include <string>
//#include <flann/test/flann_tests.h>
//#include <flann/util/timer.h>
//#include <flann/io/hdf5.h>

using namespace flann;
/*
clock_t start_time_;
void start_timer(const std::string& message = "")
{
    if (!message.empty()) {
        printf("%s", message.c_str());
        fflush(stdout);
    }
    start_time_ = clock();
}

double stop_timer()
{
    return double(clock()-start_time_)/CLOCKS_PER_SEC;
}
*/
timespec ts_;

void start_timer(const std::string& message = "")
{
    if (!message.empty()) {
        printf("%s", message.c_str());
        fflush(stdout);
    }
    clock_gettime(CLOCK_REALTIME, &ts_);
}

double stop_timer()
{
    timespec ts2;
    clock_gettime(CLOCK_REALTIME, &ts2);
    return double((ts2.tv_sec-ts_.tv_sec)+(ts2.tv_nsec-ts_.tv_nsec)/1e9);
}

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

    unsigned long foo = rows*cols;
    //__int64 foo2 = foo * sizeof(float);

    data = new(std::nothrow)float[foo];
    //data = (float*) malloc(rows*cols*sizeof(float));

    while (!data) {
        printf("Cannot allocate memory.\n");
        data = new(std::nothrow)float[foo];
        //exit(1);
    }
    //else
        std::cout << "alokacia sa podarila.\n";

    //free(data);

    p = data;

    for (int i = 0; i<rows; ++i)
    {
        //char mystring [62];   //preskakuje nepotrebne riadky s id
        //fgets(mystring,60,fin);
        for (int j = 0; j<cols; ++j)
        {
            fscanf(fin, "%g ", p);
            p++;
        }
    }
    fclose(fin);
    return data;
}

float* read_points2(const char* filename, int rows, int cols, std::string * id)
{
        float* data = NULL;
    std::ifstream is(filename);
    if(is.is_open())
        std::cout << "Subor je otvoreny." << std::endl;
    else
        exit(1);

    //Create a vector to store the data
    unsigned long foo = rows*cols;
    __int64 foo2 = foo * sizeof(float);
    //std::cout << foo2 << std::endl; //<< foo*sizeof(float) << std::endl;
    data = new(std::nothrow)float[foo];


    int i=0;
    while (!data) {
        i++;
        printf("Cannot allocate memory.\n");
        data = new(std::nothrow)float[foo];
        if(i == 10)
            exit(1);
    }
    std::cout << "alokacia sa podarila.\n";

    float *p = data;
    //std::string *pomId = id;
    //StartStopTimer t;
    //t.start();

    std::string line;
    for (int j = 0; j<rows; ++j)
    {
        //t.reset();
        //t.start();
        is.seekg(49, std::ios::cur);

        getline(is,line);
        //std::cout << line << " " << j << std::endl;
        //*pomId = line;
        id[j] = line;
        //std::cout << id[j] << " " << j << std::endl;
        //pomId++;
        getline(is,line);


        //std::cout << t.stop() << "s riadok nacitany" << std::endl;
        //t.reset();
        //t.start();

        //std::stringstream stream(line);
        char* pEnd;
        *p = strtof(line.c_str(), &pEnd);
        p++;

        for(int i = 1; i < cols; ++i)
        {
           *p = strtof(pEnd, &pEnd);
           //stream >> *p;
           //std::cout << *p << " pocet vektorov uz:" << j << std::endl;
           //if(j == 0 && i == 5) std::cout << *p;
           p++;
        }
        //std::cout << t.stop() << "s riadok rozparsovany" << std::endl;
        //t.stop();
    }

    is.close();
    return data;
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
            fprintf(fout,"%f ",*p);
            p++;
        }
        fprintf(fout,"\n");
    }
    fclose(fout);
}

void write_results_int(const char* filename, int *data, int rows, int cols)
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

void write_full_results(const char* filename, float *dists,int * indices, std::string *queryId,std::string *datasetId, int rows, int cols)
{
    FILE * fout;
    float * p;
    int * indic;
    int i,j;

    fout = fopen(filename,"w");
    if (!fout) {
        printf("Cannot open output file.\n");
        exit(1);
    }

    p = dists;
    indic = indices;

    for (i=0;i<rows;++i) {
        fprintf(fout,"query=%s\n",queryId[i].c_str());
        for (j=0;j<cols-1;++j) {
            fprintf(fout,"%f: ",*p);
            fprintf(fout,"%s, ",datasetId[*indic].c_str());
            p++;
            indic++;
        }
        fprintf(fout,"%f: ",*p);
        fprintf(fout,"%s\n",datasetId[*indic].c_str());
        p++;
        indic++;
        //std::cout << i << std::endl;
    }
    fclose(fout);
}

int main()
{
    int nn = 10;
    int rows = 1000;  // number of rows in dataset
    int cols = 4096;  // dimension of vectors
    int t_rows = 100; // number of rows in query

    //int rows = 100000;  // number of rows in dataset
    //int cols = 3;  // dimension of vectors
    //int t_rows = 100; // number of rows in query

    std::string * query_id = new std::string[t_rows];
    std::string * dataset_id = new std::string[rows];

    start_timer("Reading dataset...");    
    //float* dataset2 = read_points("../data/vector-L2-dim3-100000.data", rows, cols);
    float* dataset2 = read_points2("../data/profi-neuralnet-100K.data", rows, cols, dataset_id);
    printf("done (%g seconds)\n", stop_timer());


    start_timer("Reading query...");
    //float* query2 = read_points("../data/queryset-dim32-100.data", t_rows, cols);
    float* query2 = read_points2("../data/profi-neuralnet-1000-query.data", t_rows, cols, query_id);
    printf("done (%g seconds)\n", stop_timer());


    //Index<L2<float> > index2;
    //index2.load_saved_index(dataset,"index100000.data",dists);

    Matrix<float> dataset(dataset2, rows, cols);
    Matrix<float> query(query2, t_rows, cols);

    Matrix<int> indices(new int[query.rows*nn], query.rows, nn);
    Matrix<float> dists(new float[query.rows*nn], query.rows, nn);


    // construct an randomized kd-tree index using 4 kd-trees
    //Index<L2<float> > index(dataset, flann::KDTreeIndexParams(4));
    Index<L1<float> > index(dataset, flann::AutotunedIndexParams(0.9,0.01,0,0.1));
    //Index<L2<float> > index(dataset, flann::SavedIndexParams("Autotuned_index_90per.idx"));

    start_timer("Building autotuned index...");
    index.buildIndex();
    printf("done (%g seconds)\n", stop_timer());

    /*
    const IndexParams index_params = index.getParameters();
    printf("The index has the following parameters:\n");
    flann::print_params(index_params);
    */
    flann::SearchParams searchParams(128);
    searchParams.cores = 0;
    //index.knnSearch(query, indices, dists, nn, searchParams);

    start_timer("Searching KNN...");
    index.knnSearch(query, indices, dists, nn, flann::SearchParams(FLANN_CHECKS_AUTOTUNED) );
    //index.knnSearch(query, indices, dists, nn, flann::SearchParams(128) );
    //index.knnSearch(query, indices, dists, nn, searchParams);
    printf("done (%g seconds)\n", stop_timer());

    //flann::save_to_file(indices,"result.hdf5","result");
    std::cout << "zapisujem vzdialenost";
    write_results_float("test distance.data",dists.ptr(), t_rows, nn);
    write_results_int("test indices.data",indices.ptr(), t_rows, nn);
    std::cout << "... done" << std::endl;
    write_full_results("groundtruth-profineural3.txt",dists.ptr(),indices.ptr(),query_id,dataset_id,t_rows,nn);
    //write_results_float("ulozeneQuery.data",dists.ptr(), t_rows, nn);

    //index.save("Autotuned_index_10per.idx");
    //std::cout << dataset_id[903] << dataset_id[791] << std::endl;
    //std::cout << dataset_id[884] << dataset_id[288] << std::endl;

    //std::cout << *index.getPoint(903) << " " << *index.getPoint(791) << " " << *index.getPoint(30) << std::endl;
    //std::cout << *index.getPoint(573) << " " << *(index.getPoint(1)+1) << " " << *(index.getPoint(1)+2) << std::endl;

    delete[] dataset2;
    delete[] query2;
    delete[] indices.ptr();
    delete[] dists.ptr();

}



