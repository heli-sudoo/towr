/**
 @file    constraint_container.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    May 30, 2016
 @brief   Provides a class to combine knowledge of individual constraints.
 */

#ifndef USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_CONSTRAINT_CONTAINER_H_
#define USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_CONSTRAINT_CONTAINER_H_

#include <xpp/zmp/a_constraint.h>
#include <map>
#include <memory>

namespace xpp {
namespace zmp {

/** @brief Knows about all constraints and gives information about them.
  *
  * For every constraint that \c ConstraintContainer knows about, it will return
  * the constraint violations and the acceptable bounds.
  */
class ConstraintContainer {
public:
  typedef AConstraint::VectorXd VectorXd;
  typedef AConstraint::VecBound VecBound;
  typedef std::shared_ptr<AConstraint> ConstraintPtr;

  ConstraintContainer ();
  virtual ~ConstraintContainer ();

  void AddConstraint (ConstraintPtr constraint,
                      const std::string& name);

  AConstraint& GetConstraint(const std::string& name);

  VectorXd EvaluateConstraints ();
  VecBound GetBounds () const;
  void Refresh ();

private:
  std::map<std::string, ConstraintPtr > constraints_;
  VectorXd g_;
  VecBound bounds_;

  bool bounds_up_to_date_;
};

} /* namespace zmp */
} /* namespace xpp */

#endif /* USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_CONSTRAINT_CONTAINER_H_ */