#include <ros/ros.h>
#include <string>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

using namespace std;

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int moveToPosition(MoveBaseClient& ac, move_base_msgs::MoveBaseGoal& goal, 
   char* mesg1, char* mesg2)
{
    int ret = -1;
    // Send the goal position and orientation for the robot to reach
    ROS_INFO(mesg1);
    ac.sendGoal(goal);

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("%s x:%.1f, y:%.1f, w:%.1f", mesg2,\
 	    goal.target_pose.pose.position.x,\
	    goal.target_pose.pose.position.y,\
	    goal.target_pose.pose.orientation.w);
        sleep(5);
        ret = 0;
    }
    else
        ROS_INFO("The base failed to move forward to position");
    return ret;
}

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define the pickup position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -3.6;
  goal.target_pose.pose.position.y = 7.0;   //-8.6;
  goal.target_pose.pose.orientation.w = 1.0;
  char mesg1[50]; strcpy(mesg1, "Going to pickup area");
  char mesg2[50]; strcpy(mesg2, "Hooray, the robot is in pick up area at");

  // Go to there
  int status = moveToPosition(ac, goal, mesg1, mesg2);
  if(status == 0)
  {
      ROS_INFO("Success in pick up.");
      // Define the drop off position and orientation for the robot to reach
      goal.target_pose.pose.position.x = 4.0;
      goal.target_pose.pose.position.y = 4.0;
      goal.target_pose.pose.orientation.w = 1.0;
      strcpy(mesg1, "Going to drop off are");
      strcpy(mesg2, "Hooray, the robot is in drop off area at");
      // Go to there
      status = moveToPosition(ac, goal, mesg1, mesg2);
  }
  if(status == 0) ROS_INFO("Transport jo job completed with SUCCESS!");
  else ROS_INFO("Job FAILED!");
  sleep(5);
  return 0;
}
