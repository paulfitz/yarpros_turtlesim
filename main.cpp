#include <yarp/os/all.h>
#include <iostream>
#include <cmath>

#include "Velocity.h"
#include "Pose.h"
#include "TeleportAbsoluteIn.h"
#include "TeleportAbsoluteOut.h"
#include "TeleportRelativeIn.h"
#include "TeleportRelativeOut.h"
#include "EmptyIn.h"
#include "EmptyOut.h"
#include "SpawnIn.h"
#include "SpawnOut.h"
#include "KillIn.h"
#include "KillOut.h"
#include "SetPenIn.h"
#include "SetPenOut.h"


int main(int argc, char *argv[]) {
    yarp::os::Network yarp;



    // reset service
    const std::string reset_port_name("/yarpros_turtlesim/reset");
    const std::string reset_service("/turtlesim#/reset");

    yarp::os::Port reset_port;
    reset_port.openFake(reset_port_name.c_str());
    reset_port.addOutput(reset_service.c_str());

    EmptyIn resetIn;
    EmptyOut resetOut;
    reset_port.write(resetIn, resetOut);



    // command_velocity topic
    const std::string command_velocity_port_name("/yarpros_turtlesim/turtle1/command_velocity");
    const std::string command_velocity_topic("topic://turtle1/command_velocity");
    yarp::os::Port command_velocity_port;
    command_velocity_port.open(command_velocity_port_name.c_str());

    if (!yarp.connect(command_velocity_port_name.c_str(), command_velocity_topic.c_str())) {
        std::cout << "Error! Could not connect to topic " << command_velocity_topic << std::endl;
        return -1;
    }

    Velocity v;
    v.linear = 2.0;
    v.angular = 0;
    command_velocity_port.write(v);




    // pose topic
    const std::string pose_port_name("/yarpros_turtlesim/turtle1/pose");
    const std::string pose_topic("topic://turtle1/pose");
    yarp::os::BufferedPort<Pose> pose_port;
    pose_port.open(pose_port_name.c_str());

    if (!yarp.connect(pose_topic.c_str(), pose_port_name.c_str())) {
        std::cout << "Error! Could not connect to topic " << pose_topic << std::endl;
        return -1;
    }




    // teleport_absolute service
    const std::string teleport_absolute_port_name("/yarpros_turtlesim/turtle1/teleport_absolute");
    const std::string teleport_absolute_service("/turtlesim#/turtle1/teleport_absolute");
    yarp::os::Port teleport_absolute_port;
    teleport_absolute_port.openFake(teleport_absolute_port_name.c_str());
    teleport_absolute_port.addOutput(teleport_absolute_service.c_str());

    TeleportAbsoluteIn teleportAbsoluteIn;
    teleportAbsoluteIn.x = 5;
    teleportAbsoluteIn.y = 5;
    teleportAbsoluteIn.theta = 0;
    TeleportAbsoluteOut teleportAbsoluteOut;
    teleport_absolute_port.write(teleportAbsoluteIn, teleportAbsoluteOut);




    // teleport_relative service
    const std::string teleport_relative_port_name("/yarpros_turtlesim/turtle1/teleport_relative");
    const std::string teleport_relative_service("/turtlesim#/turtle1/teleport_relative");
    yarp::os::Port teleport_relative_port;
    teleport_relative_port.openFake(teleport_relative_port_name.c_str());
    teleport_relative_port.addOutput(teleport_relative_service.c_str());

    TeleportRelativeIn teleportRelativeIn;
    teleportRelativeIn.linear = -1;
    teleportRelativeIn.angular = -M_PI/2;
    TeleportRelativeOut teleportRelativeOut;
    teleport_relative_port.write(teleportRelativeIn, teleportRelativeOut);




    // clear service
    const std::string clear_port_name("/yarpros_turtlesim/clear");
    const std::string clear_service("/turtlesim#/clear");

    yarp::os::Port clear_port;
    clear_port.openFake(clear_port_name.c_str());
    clear_port.addOutput(clear_service.c_str());

    EmptyIn clearIn;
    EmptyOut clearOut;
    clear_port.write(clearIn, clearOut);







    // spawn service
    const std::string spawn_port_name("/yarpros_turtlesim/spawn");
    const std::string spawn_service("/turtlesim#/spawn");
    yarp::os::Port spawn_port;
    spawn_port.openFake(clear_port_name.c_str());
    spawn_port.addOutput(spawn_service.c_str());

    SpawnIn spawnIn;
    SpawnOut spawnOut;
    spawnIn.x = 3.0;
    spawnIn.y = 3.0;
    spawnIn.theta = M_PI;
    spawn_port.write(spawnIn, spawnOut);

    std::cout << "New turtle name = " << spawnOut.name << std::endl;




    // kill service
    const std::string kill_port_name("/yarpros_turtlesim/kill");
    const std::string kill_service("/turtlesim#/kill");
    yarp::os::Port kill_port;
    kill_port.openFake(clear_port_name.c_str());
    kill_port.addOutput(kill_service.c_str());

    KillIn killIn;
    KillOut killOut;
    killIn.name = spawnOut.name;
    kill_port.write(killIn, killOut);

    std::cout << "Killed turtle " << killIn.name << std::endl;


    // set_pen service
    const std::string set_pen_port_name("/yarpros_turtlesim/turtle1/set_pen");
    const std::string set_pen_service("/turtlesim#/turtle1/set_pen");
    yarp::os::Port set_pen_port;
    set_pen_port.openFake(set_pen_port_name.c_str());
    set_pen_port.addOutput(set_pen_service.c_str());

//     if (!yarp.connect(set_pen_service_local_port_name.c_str(), set_pen_service_remote_port_name.c_str())) {
//         std::cout << "Error! Could not connect to service " << set_pen_service_remote_port_name << std::endl;
//         return -1;
//     }

    SetPenIn setPenIn;
    setPenIn.r = 0;
    setPenIn.g = 255;
    setPenIn.b = 0;
    setPenIn.width = 1;
    setPenIn.off = 0;
    SetPenOut setPenOut;
    set_pen_port.write(setPenIn, setPenOut);




    while (1) {
        Velocity v;
        v.linear = 4.0;
        v.angular = 0.5;

        command_velocity_port.write(v);

        yarp::os::Time::delay(1);

        v.linear = 1.5;
        v.angular = 3.0;
        command_velocity_port.write(v);

        yarp::os::Time::delay(1);
        Pose *p = pose_port.read();
        if(p != NULL) {
//             if(p.linear_velocity == 0 && p.angular_velocity == 0) {
            std::cout << "pose: x = "            << p->x
                      << ", y = "                << p->y
                      << ", theta = "            << p->theta
                      << ", linear_velocity = "  << p->linear_velocity
                      << ", angular_velocity = " << p->angular_velocity
                      << std::endl;
//             }
        } else {
            std::cerr << "Couldn't read pose" << std::endl;
        }

    }
    return 0;
}
