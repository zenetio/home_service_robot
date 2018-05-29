#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
//#include <nav_msgs/OccupancyGrid.h>

bool change_marker = true;

int step = 0;

/* callback called each time there is a odom msgs available
 *
 */
void odom_Callback(const nav_msgs::Odometry::ConstPtr& msg)
{
  double x, y, z;

  x = msg->pose.pose.position.x;
  y = msg->pose.pose.position.y;
  z = msg->pose.pose.position.z;

  // check the position used to pick up the object
  ROS_INFO("Position-> x: [%.1f], y: [%.1f], z: [%.1f], s: [%i]", x,y,z,step);
  if((x < -3.3 && x > -3.8) && (y < 7.2 && y > 6.7) && (step == 1) && !change_marker ){
      step = 2;
      change_marker = true;
      ROS_INFO("--> Picking up <--");
  // check the position used to drop off the object
  }else if((x < 4.2 && x > 3.8) && (y < 4.1 && y > 3.7) && (step == 2) && !change_marker ){
      step = 3;
      change_marker = true;
      ROS_INFO("--> Dropping off <--");
  }
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "marker_base");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  // subscribe to odom
  ros::Subscriber odom_sub = n.subscribe("/odom", 10, odom_Callback);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CYLINDER;
  int count = 0;
  step = 1;
  //is_moving = TRUE;
  change_marker = true;

  while (ros::ok() )
  {
    while(1)
    {
      if(change_marker) break;
      ros::spinOnce();	// process queue data once per second
      r.sleep();
      ros::Duration(1.0).sleep();
    }
    
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/odom";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "marker_base";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    if(step == 1 || step == 3) marker.action = visualization_msgs::Marker::ADD;
    if(step == 2 || step == 4) marker.action = visualization_msgs::Marker::DELETE;
    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    if(step == 1){
      marker.pose.position.x = -3.6;
      marker.pose.position.y = 7.0;   //-8.6;
    }else if(step == 3){
      marker.pose.position.x = 4.0;
      marker.pose.position.y = 4.0;
    }
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.6;
    marker.scale.y = 0.6;
    marker.scale.z = 0.2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
    

    marker.lifetime = ros::Duration();
    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);
    change_marker = false;
  }
}
