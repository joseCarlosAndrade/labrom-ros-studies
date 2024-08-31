import rospy

# defining types
class Subscriber:
    def __init__(self, name : str, topic : str,  msg_type : any, callback):
        self.name = name
        self.topic = topic
        self.msg_type = msg_type
        self.callback = callback

class Publisher:
    def __init__(self, name : str, topic : str, msg_type : any, queue_size : int = 10, pub : rospy.Publisher = None):
        self.name = name
        self.topic = topic
        self.msg_type = msg_type
        self.queue_size = queue_size
        self.pub = pub

# defining the wrapper

class Wrapper:
    # todo: does this need to be static?
    wrapper_node = None
    
    def __init__(self, node=None):
        if node == None:
            # initialize a ros node here
            Wrapper.wrapper_node = rospy.init_node("wrapper_default_node", anonymous=True)
            rospy.logwarn("No Node provided, init Wrapper default node")

        # maps to ros functionality
        self.wrapper_subscribers : dict[str, Subscriber] = {}
        self.wrapper_publishers : dict[str, Publisher] = {}
        self.wrapper_services = {}  


    def addSubscriber(self, subscriber : Subscriber) -> bool: 
        """Adds a subscriber to the subs map, mapping it by its name

        Args:
            subscriber (Subscriber): the subscriber in question

        Returns:
            bool: if the operation was sucessfull (sub added) or not (there is already a subscriber with this name)
        """
        if subscriber.name in self.wrapper_subscribers: # subscriber already exist with this name
            return False   
        
        # adding new subscriber
        self.wrapper_subscribers[subscriber.name] = subscriber
        return True
    
    def addPublisher(self, publisher : Publisher) -> bool:
        """Adds a publisher to the subs map, mapping it by its name

        Args:
            publisher (Publisher): the publisher in question

        Returns:
            bool: if the operation was sucessfull (pub added) or not (there is already a publisher with this name)
        """
        if publisher.name in self.wrapper_publishers:
            return False
        
        # adding nwe publisher
        self.wrapper_publishers[publisher.name] = publisher

        if publisher.pub == None: # if the publisher wasnt initialized yet, then do it
            self.wrapper_publishers[publisher.name].pub = rospy.Publisher(publisher.topic, publisher.msg_type, queue_size=publisher.queue_size)
            
        return True

    def initSubscriber(self, name : str):
        try:
            sub = self.wrapper_subscribers[name]

            rospy.Subscriber(sub.topic, sub.msg_type, callback=sub.callback)
            return True
        
        except Exception as err:
            rospy.logerr(err)
            return False

    def publishMessage(self, name : str, message) :
        try: 
            pub = self.wrapper_publishers[name]

            # print(type(message))

            
            # rospy.loginfo("Publishing message '", message, "' on topic: ", pub.topic)
            pub.pub.publish(message)
            rospy.loginfo(message)

        except Exception as err :
            rospy.logerr(err)
            rospy.logerr("euta")
        

    def spin(self):
        rospy.spin()