#include"ros/ros.h"
#include"sensor_msgs/JointState.h"
#include"std_msgs/String.h"
#include <iostream>
#include "cpp_sampler/cpp_utils.h"


class PSP
{
    public:
        PSP(ros::NodeHandle *nodehandle, std::string name):nh_(*nodehandle)
         {
            pub = nh_.advertise<std_msgs::String>(name + "_state", 1);
            sub = nh_.subscribe(name, 1000, &PSP::callback, this);
            timer = nh_.createTimer(ros::Duration(0.1), &PSP::main_loop, this);
            nh_.getParam(name,data_);
            name_ = name;
         }

          void callback(const std_msgs::String& msg)
         {
           data_ = msg.data;
           nh_.setParam(name_,data_);
         }

         void main_loop(const ros::TimerEvent &)
         {
             std_msgs::String msg;
             msg.data = data_;
             pub.publish(msg);
         }

         std::string get_value()
         {
            return data_;
         }


    private:
        ros::NodeHandle nh_;
        ros::Publisher pub;
        ros::Subscriber sub;
        ros::Timer timer;
        std::string data_, name_;
};

class PSP_mode
{
    public:
        PSP_mode(ros::NodeHandle *nodehandle, std::string name, std::vector<std::string> mode_list):nh_(*nodehandle)
         {
            pub = nh_.advertise<std_msgs::String>(name + "_state", 1);
            list_pub = nh_.advertise<std_msgs::String>(name + "_list", 1);
            sub = nh_.subscribe(name, 1000, &PSP_mode::callback, this);
            timer = nh_.createTimer(ros::Duration(0.1), &PSP_mode::main_loop, this);

            data_ = mode_list[0];
            nh_.getParam(name,data_);

            name_ = name;
            mode_list_ = mode_list;
         }

          void callback(const std_msgs::String& msg)
         {
           data_ = msg.data;
           nh_.setParam(name_,data_);
         }

         void main_loop(const ros::TimerEvent &)
         {
             std_msgs::String msg;
             msg.data = data_;
             pub.publish(msg);

             std_msgs::String msg2;
             msg2.data = list2string(mode_list_);
             list_pub.publish(msg);
         }

         std::string get_value()
         {
            return data_;
         }


    private:
        ros::NodeHandle nh_;
        ros::Publisher pub, list_pub;
        ros::Subscriber sub;
        ros::Timer timer;
        std::string data_, name_;
        std::vector<std::string> mode_list_;

};

class Basic
{
    public:
        Basic(ros::NodeHandle *nodehandle):nh_(*nodehandle)
         {
            pub = nh_.advertise<std_msgs::String>("/data", 5);
            sub = nh_.subscribe("/data", 1000, &Basic::callback, this);
            timer = nh_.createTimer(ros::Duration(0.1), &Basic::main_loop, this);
         }

          void callback(const std_msgs::String& msg)
         {
           std::cout << msg.data << std::endl;
         }

         void main_loop(const ros::TimerEvent &)
         {
            // implement the state machine here
             std_msgs::String msg;
             msg.data = "bbb";
             pub.publish(msg);
         }

    private:
        ros::NodeHandle nh_;
        ros::Publisher pub;
        ros::Subscriber sub;
        ros::Timer timer;
};
