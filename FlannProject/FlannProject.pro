QMAKE_CFLAGS += -std=ansi
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += "C:\Users\Durky\Desktop\test\FlannProject-build-Desktop_Qt_5_0_1_MinGW_32bit-Debug\debug\libflann.dll" \
        "C:\Users\Durky\Desktop\test\FlannProject-build-Desktop_Qt_5_0_1_MinGW_32bit-Debug\debug\libflann_cpp.dll"

SOURCES += main.cpp

HEADERS += \
    flann/general.h \
    flann/flann.hpp \
    flann/flann.h \
    flann/defines.h \
    flann/config.h \
    flann/mpi/server.h \
    flann/mpi/queries.h \
    flann/mpi/matrix.h \
    flann/mpi/index.h \
    flann/mpi/client.h \
    flann/algorithms/nn_index.h \
    flann/algorithms/lsh_index.h \
    flann/algorithms/linear_index.h \
    flann/algorithms/kmeans_index.h \
    flann/algorithms/kdtree_single_index.h \
    flann/algorithms/kdtree_index.h \
    flann/algorithms/kdtree_cuda_builder.h \
    flann/algorithms/kdtree_cuda_3d_index.h \
    flann/algorithms/hierarchical_clustering_index.h \
    flann/algorithms/dist.h \
    flann/algorithms/composite_index.h \
    flann/algorithms/center_chooser.h \
    flann/algorithms/autotuned_index.h \
    flann/algorithms/all_indices.h \
    flann/util/timer.h \
    flann/util/serialization.h \
    flann/util/saving.h \
    flann/util/sampling.h \
    flann/util/result_set.h \
    flann/util/random.h \
    flann/util/params.h \
    flann/util/object_factory.h \
    flann/util/matrix.h \
    flann/util/lsh_table.h \
    flann/util/logger.h \
    flann/util/heap.h \
    flann/util/dynamic_bitset.h \
    flann/util/cutil_math.h \
    flann/util/any.h \
    flann/util/allocator.h

