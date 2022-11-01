#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

double pick_dest_x = 0.0;
double pick_dest_y = 0.0;
double drop_dest_x = 0.0;
double drop_dest_y = 0.0;
void position_det(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
 double x = msg->pose.pose.position.x;
ROS_INFO("%f",msg->pose.pose.position.x);
ROS_INFO("%f",msg->pose.pose.position.x);
  double y = msg->pose.pose.position.y;
  if(x >= -2.7 && x <= -2.3 && y >= -0.85 && y <= -0.65){
    pick_dest_x = 1.0 ;
    pick_dest_y = 1.0 ;

  }
  if (x >= -4.2 && x <= -3.8 && y >= -3.6 && y <= -2.8){
   pick_dest_x = 0.1 ;
    pick_dest_y = 0.1 ;
    drop_dest_x = 1.0 ;
    drop_dest_y = 1.0 ;
  }
ROS_INFO("pick_dest_x: %f", pick_dest_x);
ROS_INFO("pick_dest_y: %f", pick_dest_y);
ROS_INFO("drop_dest_x: %f", drop_dest_x);
ROS_INFO("drop_dest_y: %f", drop_dest_y);

}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
ros::Subscriber pose=n.subscribe("amcl_pose",10,position_det);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

if (pick_dest_x == 0.0 && pick_dest_y == 0.0) {
    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;
 

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = -2.614;
    marker.pose.position.y = -0.765;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 0.4;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 1.5f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    
    // Publish the marker

 marker_pub.publish(marker);

}
else {
 ros::spin();

    if (pick_dest_x == 1.0 && pick_dest_y == 1.0) {
     marker.action = visualization_msgs::Marker::DELETE;
     marker_pub.publish(marker);
     
    
    }
else {
    if (drop_dest_x == 1.0 && drop_dest_y == 1.0) {
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = -4.19;
      marker.pose.position.y = -3.23;
      marker.pose.position.z = 0;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.0;
      marker.pose.orientation.w = 0.4;
      marker_pub.publish(marker);
    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 1.5f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
  
    }
}
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
     
      return 0;
      }

      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);

    }
     
}

   ros::spinOnce();
   r.sleep();
  }
}
