#pragma once
#include <glm/glm.hpp>

namespace im_param {

    template<
        typename backend_type,
        int Dim, class T, glm::qualifier P,
        std::enable_if_t<Dim <= 4, bool> = true
    >
    backend_type& parameter(
        backend_type& backend, 
        const std::string& name, 
        glm::vec<Dim,typename T, P>& value, 
        glm::vec<Dim,typename T, P> min = glm::vec<Dim, typename T, P>(static_cast<T>(0)),
        glm::vec<Dim,typename T, P> max = glm::vec<Dim, typename T, P>(static_cast<T>(1)),
        glm::vec<Dim,typename T, P> scale = glm::vec<Dim, typename T, P>(static_cast<T>(1))
    )
    {
        parameter(backend, name, &value.x, Dim, &min.x, &max.x, &scale.x);
        return backend;
    }

    template<
        int Columns,
        int Rows, 
        class T, 
        glm::qualifier P
    >
    glm::mat<Columns, Rows, typename T, P> glm_mat_with_value(T value)
    {
        glm::mat<Columns, Rows, typename T, P> result;
        for (int i = 0; i < Columns; ++i)
        {
            for (int j = 0; j < Rows; ++j)
            {
                result[i][j] = value;
            }
        }
        return result;
    }

    template<
        typename backend_type,
        int Columns,
        int Rows, 
        class T, 
        glm::qualifier P//,
        // std::enable_if_t<Columns <= 4 && Rows <= 4, bool> = true
    >
    backend_type& parameter(
        backend_type& backend, 
        const std::string& name, 
        glm::mat<Columns, Rows, typename T, P>& value, 
        glm::mat<Columns, Rows, typename T, P> min = glm_mat_with_value<Columns, Rows, typename T, P>(static_cast<typename T>(0)),
        glm::mat<Columns, Rows, typename T, P> max = glm_mat_with_value<Columns, Rows, typename T, P>(static_cast<typename T>(1)),
        glm::mat<Columns, Rows, typename T, P> scale = glm_mat_with_value<Columns, Rows, typename T, P>(static_cast<typename T>(1))
    )
    {
        glm::mat<Rows, Columns, typename T, P> transposed = glm::transpose(value);
        glm::mat<Rows, Columns, typename T, P> transposed_min = glm::transpose(min);
        glm::mat<Rows, Columns, typename T, P> transposed_max = glm::transpose(max);
        glm::mat<Rows, Columns, typename T, P> transposed_scale = glm::transpose(scale);
        for (int j = 0; j < Rows; ++j)
        {
            using RowType = glm::vec<Columns, typename T, P>;

            RowType row = transposed[j];
            RowType row_min = transposed_min[j];
            RowType row_max = transposed_max[j];
            RowType row_scale = transposed_scale[j];
            
            std::string row_name = name + std::string("[") + std::to_string(j) + std::string("]");
            parameter(backend, row_name, row, row_min, row_max, row_scale);

            transposed[j] = row;
        }
        value = glm::transpose(transposed);
        return backend;
    }

} // namespace im_param
