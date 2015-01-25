#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <flann/flann.hpp>
//#include <flann/test/flann_tests.h>
//#include <flann/util/timer.h>
//#include <flann/io/hdf5.h>




using namespace flann;

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

template<class It>
double mystrtod(It &s, It const end)
{
    static double const pow10[] = { 1E-323, 1E-322, 1E-321, 1E-320, 1E-319, 1E-318, 1E-317, 1E-316, 1E-315, 1E-314, 1E-313, 1E-312, 1E-311, 1E-310, 1E-309, 1E-308, 1E-307, 1E-306, 1E-305, 1E-304, 1E-303, 1E-302, 1E-301, 1E-300, 1E-299, 1E-298, 1E-297, 1E-296, 1E-295, 1E-294, 1E-293, 1E-292, 1E-291, 1E-290, 1E-289, 1E-288, 1E-287, 1E-286, 1E-285, 1E-284, 1E-283, 1E-282, 1E-281, 1E-280, 1E-279, 1E-278, 1E-277, 1E-276, 1E-275, 1E-274, 1E-273, 1E-272, 1E-271, 1E-270, 1E-269, 1E-268, 1E-267, 1E-266, 1E-265, 1E-264, 1E-263, 1E-262, 1E-261, 1E-260, 1E-259, 1E-258, 1E-257, 1E-256, 1E-255, 1E-254, 1E-253, 1E-252, 1E-251, 1E-250, 1E-249, 1E-248, 1E-247, 1E-246, 1E-245, 1E-244, 1E-243, 1E-242, 1E-241, 1E-240, 1E-239, 1E-238, 1E-237, 1E-236, 1E-235, 1E-234, 1E-233, 1E-232, 1E-231, 1E-230, 1E-229, 1E-228, 1E-227, 1E-226, 1E-225, 1E-224, 1E-223, 1E-222, 1E-221, 1E-220, 1E-219, 1E-218, 1E-217, 1E-216, 1E-215, 1E-214, 1E-213, 1E-212, 1E-211, 1E-210, 1E-209, 1E-208, 1E-207, 1E-206, 1E-205, 1E-204, 1E-203, 1E-202, 1E-201, 1E-200, 1E-199, 1E-198, 1E-197, 1E-196, 1E-195, 1E-194, 1E-193, 1E-192, 1E-191, 1E-190, 1E-189, 1E-188, 1E-187, 1E-186, 1E-185, 1E-184, 1E-183, 1E-182, 1E-181, 1E-180, 1E-179, 1E-178, 1E-177, 1E-176, 1E-175, 1E-174, 1E-173, 1E-172, 1E-171, 1E-170, 1E-169, 1E-168, 1E-167, 1E-166, 1E-165, 1E-164, 1E-163, 1E-162, 1E-161, 1E-160, 1E-159, 1E-158, 1E-157, 1E-156, 1E-155, 1E-154, 1E-153, 1E-152, 1E-151, 1E-150, 1E-149, 1E-148, 1E-147, 1E-146, 1E-145, 1E-144, 1E-143, 1E-142, 1E-141, 1E-140, 1E-139, 1E-138, 1E-137, 1E-136, 1E-135, 1E-134, 1E-133, 1E-132, 1E-131, 1E-130, 1E-129, 1E-128, 1E-127, 1E-126, 1E-125, 1E-124, 1E-123, 1E-122, 1E-121, 1E-120, 1E-119, 1E-118, 1E-117, 1E-116, 1E-115, 1E-114, 1E-113, 1E-112, 1E-111, 1E-110, 1E-109, 1E-108, 1E-107, 1E-106, 1E-105, 1E-104, 1E-103, 1E-102, 1E-101, 1E-100, 1E-099, 1E-098, 1E-097, 1E-096, 1E-095, 1E-094, 1E-093, 1E-092, 1E-091, 1E-090, 1E-089, 1E-088, 1E-087, 1E-086, 1E-085, 1E-084, 1E-083, 1E-082, 1E-081, 1E-080, 1E-079, 1E-078, 1E-077, 1E-076, 1E-075, 1E-074, 1E-073, 1E-072, 1E-071, 1E-070, 1E-069, 1E-068, 1E-067, 1E-066, 1E-065, 1E-064, 1E-063, 1E-062, 1E-061, 1E-060, 1E-059, 1E-058, 1E-057, 1E-056, 1E-055, 1E-054, 1E-053, 1E-052, 1E-051, 1E-050, 1E-049, 1E-048, 1E-047, 1E-046, 1E-045, 1E-044, 1E-043, 1E-042, 1E-041, 1E-040, 1E-039, 1E-038, 1E-037, 1E-036, 1E-035, 1E-034, 1E-033, 1E-032, 1E-031, 1E-030, 1E-029, 1E-028, 1E-027, 1E-026, 1E-025, 1E-024, 1E-023, 1E-022, 1E-021, 1E-020, 1E-019, 1E-018, 1E-017, 1E-016, 1E-015, 1E-014, 1E-013, 1E-012, 1E-011, 1E-010, 1E-009, 1E-008, 1E-007, 1E-006, 1E-005, 1E-004, 1E-003, 1E-002, 1E-001, 1E+000, 1E+001, 1E+002, 1E+003, 1E+004, 1E+005, 1E+006, 1E+007, 1E+008, 1E+009, 1E+010, 1E+011, 1E+012, 1E+013, 1E+014, 1E+015, 1E+016, 1E+017, 1E+018, 1E+019, 1E+020, 1E+021, 1E+022, 1E+023, 1E+024, 1E+025, 1E+026, 1E+027, 1E+028, 1E+029, 1E+030, 1E+031, 1E+032, 1E+033, 1E+034, 1E+035, 1E+036, 1E+037, 1E+038, 1E+039, 1E+040, 1E+041, 1E+042, 1E+043, 1E+044, 1E+045, 1E+046, 1E+047, 1E+048, 1E+049, 1E+050, 1E+051, 1E+052, 1E+053, 1E+054, 1E+055, 1E+056, 1E+057, 1E+058, 1E+059, 1E+060, 1E+061, 1E+062, 1E+063, 1E+064, 1E+065, 1E+066, 1E+067, 1E+068, 1E+069, 1E+070, 1E+071, 1E+072, 1E+073, 1E+074, 1E+075, 1E+076, 1E+077, 1E+078, 1E+079, 1E+080, 1E+081, 1E+082, 1E+083, 1E+084, 1E+085, 1E+086, 1E+087, 1E+088, 1E+089, 1E+090, 1E+091, 1E+092, 1E+093, 1E+094, 1E+095, 1E+096, 1E+097, 1E+098, 1E+099, 1E+100, 1E+101, 1E+102, 1E+103, 1E+104, 1E+105, 1E+106, 1E+107, 1E+108, 1E+109, 1E+110, 1E+111, 1E+112, 1E+113, 1E+114, 1E+115, 1E+116, 1E+117, 1E+118, 1E+119, 1E+120, 1E+121, 1E+122, 1E+123, 1E+124, 1E+125, 1E+126, 1E+127, 1E+128, 1E+129, 1E+130, 1E+131, 1E+132, 1E+133, 1E+134, 1E+135, 1E+136, 1E+137, 1E+138, 1E+139, 1E+140, 1E+141, 1E+142, 1E+143, 1E+144, 1E+145, 1E+146, 1E+147, 1E+148, 1E+149, 1E+150, 1E+151, 1E+152, 1E+153, 1E+154, 1E+155, 1E+156, 1E+157, 1E+158, 1E+159, 1E+160, 1E+161, 1E+162, 1E+163, 1E+164, 1E+165, 1E+166, 1E+167, 1E+168, 1E+169, 1E+170, 1E+171, 1E+172, 1E+173, 1E+174, 1E+175, 1E+176, 1E+177, 1E+178, 1E+179, 1E+180, 1E+181, 1E+182, 1E+183, 1E+184, 1E+185, 1E+186, 1E+187, 1E+188, 1E+189, 1E+190, 1E+191, 1E+192, 1E+193, 1E+194, 1E+195, 1E+196, 1E+197, 1E+198, 1E+199, 1E+200, 1E+201, 1E+202, 1E+203, 1E+204, 1E+205, 1E+206, 1E+207, 1E+208, 1E+209, 1E+210, 1E+211, 1E+212, 1E+213, 1E+214, 1E+215, 1E+216, 1E+217, 1E+218, 1E+219, 1E+220, 1E+221, 1E+222, 1E+223, 1E+224, 1E+225, 1E+226, 1E+227, 1E+228, 1E+229, 1E+230, 1E+231, 1E+232, 1E+233, 1E+234, 1E+235, 1E+236, 1E+237, 1E+238, 1E+239, 1E+240, 1E+241, 1E+242, 1E+243, 1E+244, 1E+245, 1E+246, 1E+247, 1E+248, 1E+249, 1E+250, 1E+251, 1E+252, 1E+253, 1E+254, 1E+255, 1E+256, 1E+257, 1E+258, 1E+259, 1E+260, 1E+261, 1E+262, 1E+263, 1E+264, 1E+265, 1E+266, 1E+267, 1E+268, 1E+269, 1E+270, 1E+271, 1E+272, 1E+273, 1E+274, 1E+275, 1E+276, 1E+277, 1E+278, 1E+279, 1E+280, 1E+281, 1E+282, 1E+283, 1E+284, 1E+285, 1E+286, 1E+287, 1E+288, 1E+289, 1E+290, 1E+291, 1E+292, 1E+293, 1E+294, 1E+295, 1E+296, 1E+297, 1E+298, 1E+299, 1E+300, 1E+301, 1E+302, 1E+303, 1E+304, 1E+305, 1E+306, 1E+307, 1E+308 };
    long long b = 0, e1 = 0, e2 = 0;
    bool is_exp = false;
    do
    {
        bool negate = s != end && *s == '-';
        if (s != end && (*s == '-' || *s == '+')) { ++s; }
        bool decimal = false;
        long long &r = is_exp ? e2 : b;
        while (s != end && (*s == '.' || '0' <= *s && *s <= '9'))
        {
            if (*s != '.')
            {
                e1 -= decimal;
                char const digit = *s - '0';
                if (static_cast<unsigned long long>(r) < static_cast<unsigned long long>(r) * 10 + static_cast<unsigned char>(digit))
                {
                    r *= 10;
                    r += digit;
                }
            }
            else { decimal = true; }
            ++s;
        }
        r = negate ? -r : +r;
    } while ((is_exp = !is_exp, is_exp) && s != end && ((*s | ('e' ^ 'E')) == 'e') && (++s, is_exp));
    double const result = b * pow10[323 + (e1 + e2)];
    return result;
}

double StringToF64(const char * pString, char ** ppEnd)
{
    //---
    // Find the start of the string
    const char * pNumberStart = pString;

    // skip whitespace
    while( isspace(*pNumberStart) )
        ++pNumberStart;

    //---
    // Find the end of the string
    const char * pNumberEnd = pNumberStart;

    // skip optional sign
    if( *pNumberEnd == '-' || *pNumberEnd == '+' )
        ++pNumberEnd;

    // skip optional digits
    while( isdigit(*pNumberEnd) )
        ++pNumberEnd;

    // skip optional decimal and digits
    if( *pNumberEnd == '.' )
    {
        ++pNumberEnd;

        while( isdigit(*pNumberEnd) )
            ++pNumberEnd;
    }

    // skip optional exponent
    if(    *pNumberEnd == 'd'
        || *pNumberEnd == 'D'
        || *pNumberEnd == 'e'
        || *pNumberEnd == 'E' )
    {
        ++pNumberEnd;

        if( *pNumberEnd == '-' || *pNumberEnd == '+' )
            ++pNumberEnd;

        while( isdigit(*pNumberEnd) )
            ++pNumberEnd;
    }

    //---
    // Process the string
    const unsigned numberLen = (pNumberEnd-pNumberStart);
    char buffer[32];
    if( numberLen+1 < sizeof(buffer)/sizeof(buffer[0]) )
    {
        // copy into buffer and terminate with NUL before calling the
        // standard function
        memcpy( buffer, pNumberStart, numberLen*sizeof(buffer[0]) );
        buffer[numberLen] = '\0';
        const double result = strtod( buffer, ppEnd );

        // translate end of string back from the buffer to the input string
        if( ppEnd )
        {
            *ppEnd = const_cast<char*>( pNumberStart + (*ppEnd-buffer) );
        }

        return result;
    }
    else
    {
        // buffer was too small so just call the standard function on the
        // source input to get a proper result
        return strtod( pString, ppEnd );
    }
}

double convert( char const* source, char const** endPtr )
{
    char* end;
    int left = strtol( source, &end, 10 );
    double results = left;
    if ( *end == '.' ) {
        char* start = end + 1;
        int right = strtol( start, &end, 10 );
        static double const fracMult[]
            = { 0.0, 0.1, 0.01, 0.001, 0.0001, 0.00001 };
        results += right * fracMult[ end - start ];
    }
    if ( endPtr != NULL ) {
        *endPtr = end;
    }
    return results;
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

float* read_points2(const char* filename, int rows, int cols)
{
        float* data = NULL;
    std::ifstream is(filename);
    if(is.is_open())
        std::cout << "good" << std::endl;
    //Create a vector to store the data
    unsigned long foo = rows*cols;
    __int64 foo2 = foo * sizeof(float);
    //std::cout << foo2 << std::endl; //<< foo*sizeof(float) << std::endl;
    data = new(std::nothrow)float[foo];

    while (!data) {
        printf("Cannot allocate memory.\n");
        data = new(std::nothrow)float[foo];
    }
    std::cout << "alokacia sa podarila.\n";

    float *p = data;
    //StartStopTimer t;
    //t.start();

    std::string line;
    for (int j = 0; j<rows; ++j)
    {
        //t.reset();
        //t.start();
        is.seekg(60, std::ios::cur);
        getline(is,line);

        //std::cout << t.stop() << "s riadok nacitany" << std::endl;
        //t.reset();
        //t.start();

        std::stringstream stream(line);
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

int main()
{
    int nn = 2;
    int rows = 100000;  // number of rows in dataset
    int cols = 4096;  // dimension of vectors
    int t_rows = 1000; // number of rows in query

    //int rows = 100000;  // number of rows in dataset
    //int cols = 3;  // dimension of vectors
    //int t_rows = 100; // number of rows in query


    //float* dataset2 = read_points2("../data/profi-neuralnet-100K.data", rows, cols);
    //std::cout << "Dataset nacitany" << std::endl;

    //float* query2 = read_points2("../data/profi-neuralnet-1000-query.data", t_rows, cols);
    //std::cout << "Qeury nacitany" << std::endl;

    StartStopTimer t;
    t.start();
    start_timer("Reading dataset...");
    //float* dataset2 = read_points("../data/vector-L2-dim3-100000.data", rows, cols);

    float* dataset2 = read_points2("../data/profi-neuralnet-100K.data", rows, cols);
    //std::cout << "Dataset nacitany" << std::endl;

    printf("done (%g seconds)\n", stop_timer());
    //std::cout << t.stop() << "s nacitany vstup" << std::endl;

    t.reset();
    t.start();
    start_timer("Reading query...");
    //float* query2 = read_points("../data/queryset-dim32-100.data", t_rows, cols);

    float* query2 = read_points2("../data/profi-neuralnet-1000-query.data", t_rows, cols);
    //std::cout << "Qeury nacitany" << std::endl;
    printf("done (%g seconds)\n", stop_timer());
    //std::cout << t.stop() << "s nacitany query" << std::endl;

    //Index<L2<float> > index2;
    //index2.load_saved_index(dataset,"index100000.data",dists);

    Matrix<float> dataset(dataset2, rows, cols);
    Matrix<float> query(query2, t_rows, cols);

    //load_from_file(dataset, "dataset.hdf5", "dataset");
    //load_from_file(query, "dataset.hdf5", "query");

    Matrix<int> indices(new int[query.rows*nn], query.rows, nn);
    Matrix<float> dists(new float[query.rows*nn], query.rows, nn);

    //t.reset();
    //t.start();

    // construct an randomized kd-tree index using 4 kd-trees
    //Index<L2<float> > index(dataset, flann::KDTreeIndexParams(4));
    //Index<L2<float> > index(dataset, flann::AutotunedIndexParams(0.8,0.01,0,0.1));
    Index<L2<float> > index(dataset, flann::SavedIndexParams("index100000.dat"));

    const IndexParams index_params = index.getParameters();
    printf("The index has the following parameters:\n");
    flann::print_params(index_params);

    start_timer("Building autotuned index...");
    //index.buildIndex();
    printf("done (%g seconds)\n", stop_timer());
    //std::cout << "Index postaveny za " << t.stop() << "s" << std::endl;

    // do a knn search, using 128 checks
    //index.knnSearch(query, indices, dists, nn, flann::SearchParams(128));
    //flann::SearchParams searchParams;
    //searchParams.cores = 0;
    //index.knnSearch(query, indices, dists, nn, searchParams);

    start_timer("Searching KNN...");
    index.knnSearch(query, indices, dists, nn, flann::SearchParams(FLANN_CHECKS_AUTOTUNED) );
    printf("done (%g seconds)\n", stop_timer());

    //flann::save_to_file(indices,"result.hdf5","result");
    write_results("results2.data",indices.ptr(), t_rows, nn);
    //write_results_float("ulozeneQuery.data",dists.ptr(), t_rows, nn);

    index.save("index100000.idx");
    //std::cout << *index.getPoint(0) << " " << *(index.getPoint(0)+1) << std::endl;

    free(dataset2);
    free(query2);
    //delete[] dataset.ptr();
    //delete[] query.ptr();
    delete[] indices.ptr();
    delete[] dists.ptr();

}


