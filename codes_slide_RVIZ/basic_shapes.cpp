#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
    //cria nodo e handle
    ros::init(argc, argv, "basic_shapes"); 
    ros::NodeHandle n;
    ros::Rate r(1);

    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1); //cria publisher

    uint32_t shape = visualization_msgs::Marker::CUBE; //define o shape inicial como cubo

    while (ros::ok()) //enquanto o ros tiver online
    {
        visualization_msgs::Marker marker; //cria uma variavel marker para ser publicada no topico visualization_marker

        //INFOS DA VARIAVEL MARKER
        marker.header.frame_id = "/my_frame";
        marker.header.stamp = ros::Time::now();

        marker.ns = "basic_shapes";
        marker.id = 0;
        marker.type = shape;

        marker.action = visualization_msgs::Marker::ADD;

        marker.pose.position.x = 0;
        marker.pose.position.y = 0;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;

        marker.scale.x = 1.0;
        marker.scale.y = 1.0;
        marker.scale.z = 1.0;

        marker.color.r = 0.5f;
        marker.color.g = 0.0f;
        marker.color.b = 0.5f;
        marker.color.a = 1.0;

        marker.lifetime = ros::Duration();
        //FIM DAS INFOS DA VARIAVEL MARKER

        while (marker_pub.getNumSubscribers() < 1) //espera ter alguem inscrito no topico
        {
            if (!ros::ok())
            {
                return 0;
            }
            ROS_WARN_ONCE("Please create a subscriber to the marker");
            sleep(1);
        }

        marker_pub.publish(marker); //publica a variavel marker

        switch (shape) //muda o shape do marker para a proxima iteração
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

        r.sleep();
    }
}
