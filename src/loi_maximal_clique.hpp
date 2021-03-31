#ifndef _LOI_MAXIMAL_CLIQUE_H
#define _LOI_MAXIMAL_CLIQUE_H

#include "util.hpp"
#include "rtm.hpp"
class LoiMaximalClique
{
public:
    int v_num, max_deg, u_id;
    long long e_num;

    LoiMaximalClique();
    ~LoiMaximalClique();

    void build(const EdgeVector &_e_v);
    std::vector<int> degeneracy_order();
    int maximal_clique_bk();
    int maximal_clique_pivot();
    int maximal_clique_degen();
    int maximal_clique_bk2();

    void save_answers(const char *file_path);
    void start_report();
    void report_mc_num();

    // double intersect_time = 0.0;
    // unsigned long long intersect_cnt = 0;
    // struct timeval time_start;
    // struct timeval time_end;
private:
    EdgeVector edge_vec;
    std::vector<QVertex> graph;
    int *pool_edges = NULL;
    int *pool_sets = NULL;
    int *pool_mc = NULL, pool_mc_idx = 0, mc_num = 0;

    int *temp_set = NULL;
    int max_pool_sets_idx = 0, maximum_clique_size = 0;
    int intersect_call_time = 0, big_intersect_call_time = 0;
    int max_vector_size, root_vector_size, root_deg, root_offset, root_start;
    int max_aligned_vector_size, aligned_root_vector_size;
    int cur_index, cur_depth;    
    int p_set_idx = 0;

    Bitmap *matrix;
    Bitmap *P_vec_pool; // cache P_vec
    Bitmap *X_vec_pool; // X_vec
    Bitmap *R_vec;  // R
    Bitmap *next_vec_pool;
    int *next_set_pool;
    // Bitmap *X_vec; // X
    int *index_vec;
    int *index_pool;       
    int *R;
    bool *visited;
    int build_matrix(const QVertex &u);
    /**
     * @param deg degree of root vertex
     * */
    void set_buffer_capacity(size_t deg);
    void free_buffer();
    void dfs(int v_index, int depth);
    void dfs_pivot(int v_index, int depth);
    /** 
     * @param u the root vertex
     * @return number of triangles
     * */
    Bitmap *get_bitmap(int index)
    {
        return &matrix[index * aligned_root_vector_size];
    };
    /**
     * @param depth the depth of the recursive call (shall be <= deg)
     * @return the clique bitmap of the root vertex and the given vertex
     * */
    Bitmap *get_pvec(int depth)
    {
        return &P_vec_pool[depth * aligned_root_vector_size];
    };
    /**
     * @param depth the depth of the recursive call (shall be <= deg)
     * @return the clique bitmap of the root vertex and the given vertex
     * */
    Bitmap *get_xvec(int depth)
    {
        return &X_vec_pool[depth * aligned_root_vector_size];
    };

    /**
     * @param depth the depth of the recursive call (shall be <= deg)
     * @return the clique bitmap of the root vertex and the given vertex
     * */
    Bitmap *get_nvec(int depth)
    {
        return &next_vec_pool[depth * aligned_root_vector_size];
    };
    
    /**
     * @param depth the depth of the recursive call (shall be <= deg)
     * @return the clique bitmap of the root vertex and the given vertex
     * */
    int *get_index_by_depth(int depth)
    {
        return &index_pool[depth * root_deg];
    };
    int* get_nset(int depth){
        return &next_set_pool[depth * root_deg];
    }



    std::string matrix_to_string()
    {
        std::string result = "";
        for (int i = 0; i < root_deg; i++)
        {
            result += std::to_string(i) + " ";
            Bitmap* bitmap = &matrix[i * root_vector_size];
            result += bitmap_to_string(bitmap, root_vector_size);
            result += "\n";
        }
        result.pop_back();
        return result;
    }
    std::string to_string(int *vec, int size)
    {
        std::string result = "";
        for (int i = 0; i < size; i++)
        {
            result += std::to_string(vec[i]) + " ";
        }
        return result;
    }

    std::string bitmap_to_string(Bitmap *bitmap_vec, int vector_size)
    {
        std::string result = "";
        for (int j = 0; j < vector_size; j++)
        {
            Bitmap bitmap = bitmap_vec[j];
            for (int k = 0; k < 8; k++)
            {
                if (bitmap & (1llu << k))
                {
                    result += "1";
                }
                else
                {
                    result += "0";
                }
            }
            result += " ";
        }
        return result;
    }
};

#endif