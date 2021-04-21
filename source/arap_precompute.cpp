#include "../include/arap_precompute.h"
#include <igl/min_quad_with_fixed.h>
#include <igl/arap_linear_block.h>
#include <igl/cotmatrix.h>

void arap_precompute(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::VectorXi & b,
  igl::min_quad_with_fixed_data<double> & data,
  Eigen::SparseMatrix<double> & K)
{
// REPLACE WITH YOUR CODE
    typedef Eigen::Triplet<double> T;
    std::vector<T> tripletList;
    tripletList.reserve(F.rows()*3*6*2);

    Eigen::SparseMatrix<double> L, Aeq;
    igl::cotmatrix(V, F, L);
    igl::min_quad_with_fixed_precompute(L, b, Aeq, false, data);


    // K(n x 3n)
    K.resize(V.rows(), 3*V.rows());
    for(int n = 0; n < F.rows(); n ++)
    {
        // for each triangle
        for(int m = 0; m < 3; m ++)
        {
            int i = F(n, m%3);
            int j = F(n, (m+1)%3);
            Eigen::Vector3d edge_ij = L.coeff(i, j) * (V.row(i) - V.row(j))/6.0;
            // for each vertices
            for(int v = 0; v < 3; v ++)
            {
                // for each coords
                for(int c = 0; c < 3; c ++)
                {
                    tripletList.push_back(T(i, c + 3 * F(n, (m + v) % 3), edge_ij(c)));
                    tripletList.push_back(T(j, c + 3 * F(n, (m + v) % 3), -edge_ij(c)));
                }
            }
        }
    }
    K.setFromTriplets(tripletList.begin(), tripletList.end());

}

