#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_broadcaster.h>
#include <sstream>
#include <cmath>
#include <vector>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>
    MoveBaseClient;

MoveBaseClient* ac;

move_base_msgs::MoveBaseGoal goal;

void setPose(move_base_msgs::MoveBaseGoal &goal, double p_x, double p_y, double p_z, double p_w)
{
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = p_x;
    goal.target_pose.pose.position.y = p_y;
    goal.target_pose.pose.orientation.z = p_z;
    goal.target_pose.pose.orientation.w = p_w;

    ac->sendGoal(goal);
    ac->waitForResult();
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "navigation_goals");

    ac = new MoveBaseClient("move_base", true);

    while (!ac->waitForServer(ros::Duration(5.0)))
    {
       ROS_INFO("Waiting for the move_base action server");
    }

    ros::Rate loop_rate(20);
    while (ros::ok())
    {
        ROS_INFO("Sending goal");

        setPose(goal, 4.69468593597, 1.51777780056, 0.998965240165, 0.0454802038426);
        setPose(goal, 1.9788441658, 1.98600053787, -0.08488856055, 0.996390451724);

        if (ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        {
           ROS_INFO("You have arrived to the goal position");
        }

        else
        {
           ROS_INFO("The base failed for some reason");
        }

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;

}
