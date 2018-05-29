#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

void odom_Callback(const nav_msgs::Odometry::ConstPtr& msg)
{
  ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,
          msg->pose.pose.position.y, msg->pose.pose.position.z);
  if(msg->pose.pose.position.x == -6.0 && msg->pose.pose.position.y == -5.9) 
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "marker_base");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  // subscribe to odom
  ros::Subscriber odom_sub = n.subcribe("/odom", 10, odom_Callback);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CYLINDER;
  int count = 0;
  while (ros::ok() && count < 4)
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "marker_base";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    if(count == 0 || count ==2) marker.action = visualization_msgs::Marker::ADD;
    if(count == 1 || count ==3) marker.action = visualization_msgs::Marker::DELETE;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    if(count == 0){
      marker.pose.position.x = -6.0;
      marker.pose.position.y = -5.9;
    }else if(count == 2){
      marker.pose.position.x = 0.0;
      marker.pose.position.y = -4.5;
    }
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
    

    marker.lifetime = ros::Duration();
    //ros::Duration d(5);
    //marker.lifetime = d;
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
/*
    // Cycle between different shapes
    switch (shape)
    {
    case visualization_msgs::Marker::CUBE:
      shape = visualization_msgs::Marker::SPHERE;
      break;
    case visualization_msgs::Marker::SPHERE:
      shape = visualization_msgs::Marker::ARROW;
      break;
    case visualization_msgs::Marker::ARROW:
      shape = visualization_msgs::Marker::CYLINDER;
      break;
    case visualization_msgs::Marker::CYLINDER:
      shape = visualization_msgs::Marker::CUBE;
      break;
    }
*/
    //r.sleep();
    if(count == 3) break;
    ros::Duration(2.5).sleep();
    count++;
    //marker.action = visualization_msgs::Marker::DELETE;
    //marker_pub.publish(marker);
    //marker.pose.position.x = 0.0;
    //marker.pose.position.y = -4.5;
    //marker.lifetime = ros::Duration(2);
    //marker_pub.publish(marker);
    //ros::Duration(5).sleep();
  }
}
