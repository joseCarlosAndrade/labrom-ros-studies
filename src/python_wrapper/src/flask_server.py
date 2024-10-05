#!/usr/bin/env python


import rospy
from std_msgs.msg import String
from flask import Flask, jsonify, request
from Wrapper import Wrapper, Subscriber, Publisher

from threading import Thread
import signal, sys

class FlaskServer:
    def __init__(self):
        """Initializes the rapper using the default node called `node_name`"
        """
        self.ros_wrapper = Wrapper(node=None, node_name="flask_server")
        FlaskServer.app = Flask(__name__)

        # adding url rules to manage callbacks for each endpoint
        self.app.add_url_rule('/publish', view_func=self.__publish_callback, methods=["POST"])
        self.app.add_url_rule('/sensor_data', view_func=self.__get_sensor_callback, methods=["GET"])

        self.flask_thread = None

        self.__shared_msg = ""

    def initialize_publishers(self, topic_name : str):
        """Inits all pre configured publishers

        Args:
            topic_name (str): topic to publish into
        """
        rospy.loginfo("Initializing publishers in topic: " + topic_name )

        test_publisher = Publisher("pub", topic_name, String, 10)
        self.ros_wrapper.addPublisher(test_publisher)
    
    def initialize_subscribers(self, topic_name: str):

        rospy.loginfo("Initializing subscriber in topic: " + topic_name)

        test_subscriber = Subscriber("sub", topic_name, String, self.__sub_callback)

        self.ros_wrapper.addSubscriber(test_subscriber)

        self.ros_wrapper.initSubscriber("sub")

    def __sub_callback(self, data : String): 
        # sub callback that chanes the shared msg variable
        self.__shared_msg = data.data


    def run(self): 
        try:
            # manages signals to exit to avoid thread infinity
            signal.signal(signal.SIGINT, self.signal_handler)
            rospy.loginfo("Starting flask on port 9000")
            flask_thread = Thread(target=lambda: self.app.run(host='0.0.0.0', port=9000))
            flask_thread.start()
            

        except Exception as err :
            rospy.logerr("Could not spawn flask thread: ", err)


    def signal_handler(self, sig, frame): # this part i got from gpt!
        """Handle shutdown signals for graceful exit."""
        rospy.loginfo("Shutting down gracefully...")

        rospy.signal_shutdown("Shutting down")
        if self.flask_thread and self.flask_thread.is_alive():
            rospy.loginfo("Shuttinng flask down")
            func = request.environ.get('werkzeug.server.shutdown')
            if func:
                func()

            self.flask_thread.join()
        sys.exit(0) 
        rospy.loginfo("Shutdown complete")

    def __publish_callback(self):
        """Predefined callback to be executed when a request is made to /publish
        """
        data =  request.json
        rospy.loginfo("request received")

        # checking msg body
        if "msg" in data:
            msg = data["msg"]
            rosmsg = String()
            rosmsg.data = msg


            self.ros_wrapper.publishMessage("pub", rosmsg)
            rospy.loginfo("msg published. msg: "+ msg)

            return jsonify({"status" : "msg done!"}), 200
        else:
            rospy.logerr("msg not published. bad request")
            return jsonify({"status" : "bad request :("}), 400

    def __get_sensor_callback(self):
        """Predefined callback to return mocked data
        """

        return jsonify({"sensor data: " : self.__shared_msg}), 200
    

if __name__ == "__main__":

    flask_server = FlaskServer()

    flask_server.initialize_publishers(topic_name="flask_topic")
    flask_server.initialize_subscribers(topic_name="mocked_sensor_data")

    flask_server.run()
