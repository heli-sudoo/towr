/*
 * constraints.h
 *
 *  Created on: Mar 25, 2016
 *      Author: winklera
 */

#ifndef USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_CONSTRAINTS_H_
#define USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_CONSTRAINTS_H_

#include <Eigen/Dense>
#include <Eigen/StdVector>

#include <xpp/hyq/supp_triangle_container.h>
#include <xpp/zmp/continuous_spline_container.h>

namespace xpp {
namespace zmp {


class Constraints {

public:
  typedef std::vector<Eigen::Vector2d, Eigen::aligned_allocator<Eigen::Vector2d> > Footholds;
  typedef xpp::utils::MatVec MatVec;

  struct Bound {
    Bound(double lower, int upper) {
      lower_ = lower;
      upper_ = upper;
    }
    double lower_;
    double upper_;
  };

public:
  Constraints (const xpp::hyq::SuppTriangleContainer& supp_triangle_container,
               const xpp::zmp::ContinuousSplineContainer& zmp_spline_container);
  virtual
  ~Constraints ();


//  void AddConstraint(Bound bound,

  Eigen::VectorXd EvalContraints(const Footholds& footholds,
                                 const Eigen::VectorXd& x_coeff);
  std::vector<Bound> GetBounds() const;

  MatVec x_zmp_;
  MatVec y_zmp_;
  xpp::hyq::SuppTriangleContainer supp_triangle_container_;
  std::vector<xpp::hyq::Foothold> initial_footholds_;
  xpp::zmp::ContinuousSplineContainer zmp_spline_container_;

private:

  Eigen::VectorXd EvalSuppPolygonConstraints(const Footholds& footholds,
                                             const Eigen::VectorXd& x_coeff);

  Eigen::VectorXd EvalFootholdConstraints(const Footholds& footholds) const;

  int n_equality_constraints_;
  int n_inequality_constraints_;

};

} /* namespace zmp */
} /* namespace xpp */

#endif /* USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_CONSTRAINTS_H_ */
