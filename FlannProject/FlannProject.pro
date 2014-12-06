QMAKE_CFLAGS += -std=ansi
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

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
    flann/util/allocator.h \
    flann/ext/lz4hc.h \
    flann/ext/lz4.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../FlannProject-build-Clone_of_Desktop-Debug/release/ -llibflann_cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../FlannProject-build-Clone_of_Desktop-Debug/debug/ -llibflann_cpp
else:unix: LIBS += -L$$PWD/../FlannProject-build-Clone_of_Desktop-Debug/ -llibflann_cpp

INCLUDEPATH += $$PWD/../FlannProject-build-Clone_of_Desktop-Debug/debug
DEPENDPATH += $$PWD/../FlannProject-build-Clone_of_Desktop-Debug/debug
