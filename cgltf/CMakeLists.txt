add_library(cgltf STATIC cgltf.c)
target_include_directories(cgltf PRIVATE cgltf)
target_include_directories(cgltf INTERFACE cgltf)
