using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tweetinvi;
using Tweetinvi.Core.Interfaces;

namespace TwitterGetUsersInfo
{
    class Program
    {
        static void Main(string[] args)
        {
            //Setting app credentials
            String userAccessToken = "3230508567-My3DcP0Cq1grD6QMeBkIpLLr3R5GvG7DuQ59qyV",
                   userAccessSecret = "iHEiFx87FSag5U7IwACQ0i0LvioayDNwdPImbfNhqyNrT",
                   consumerKey = "gkAm6d1Y4WRpalx14pOmVWEc5",
                   consumerSecret = "fOmeCYFh7bgYGeCJ9mns3qts3QnhpoRCPDpzp4jsUMHW9ZpUou";
            try
            {
                TwitterCredentials.SetCredentials(userAccessToken,
                                                  userAccessSecret,
                                                  consumerKey,
                                                  consumerSecret);
            }
            catch(Exception e)
            {
                Console.WriteLine(e.StackTrace);
                return;
            }

            //Setting username
            Console.WriteLine("Enter username:");
            String userScreenName = Console.ReadLine();

            //Getting user's friends
            Console.WriteLine("Getting user's friendlist...");
            var user = User.GetUserFromScreenName(userScreenName);
            var friends = user.GetFriends(1000);
            friends.Concat(new IUser[] { user });

            //Creating nodes of the graph
            int nodeId = 1;
            Dictionary<String, Node> nodes = new Dictionary<String, Node>();
            nodes.Add(user.ScreenName, new Node(0, user.ScreenName));
            foreach(IUser friend in friends)
            {
                nodes.Add(friend.ScreenName, new Node(nodeId, friend.ScreenName));
                nodeId++;
            }

            //Creating edges of the graph
            Console.WriteLine("Getting list of retweets made by friends");
            Dictionary<Tuple<int, int> , Edge> edges = new Dictionary<Tuple<int, int>,Edge>();
            int edgeId = 0;
            foreach(IUser friend in friends)
            {
                Console.WriteLine("Getting retweets made by " + friend.ScreenName + "...");
                var retweets = friend.GetUserTimeline(100);
                if (retweets == null)
                    continue;
                Node targetNode = nodes[friend.ScreenName];
                foreach(ITweet retweet in retweets)
                {                    
                    if(retweet.IsRetweet)
                    {
                        if (nodes.ContainsKey(retweet.RetweetedTweet.Creator.ScreenName))
                        {
                            Node sourceNode = nodes[retweet.RetweetedTweet.Creator.ScreenName];
                            Tuple<int, int> edgeDirection = new Tuple<int, int>(sourceNode.Id, targetNode.Id);
                            if (!edges.ContainsKey(edgeDirection))
                            {
                                edges.Add(edgeDirection, new Edge(edgeId, edgeDirection.Item1, edgeDirection.Item2, friend.ScreenName + " - " + retweet.RetweetedTweet.Creator.ScreenName, 1));
                                edgeId++;
                            }
                            else
                            {
                                edges[edgeDirection].Weight++;
                            }
                        }
                    }                    
                }
            }
            Console.WriteLine("All retweets has been taken");

            //Setting filenames
            String edgesFilename, nodesFilename;
            Console.WriteLine("Enter nodes filename");
            nodesFilename = Console.ReadLine();
            Console.WriteLine("Enter edges filename");
            edgesFilename = Console.ReadLine();

            //Creating nodes file
            var csv = new StringBuilder();
            using(File.Create(nodesFilename))
            {
                csv.Append("Id,Label\r\n");
                foreach(KeyValuePair<String, Node> node in nodes)
                {
                    csv.Append(node.Value.Id.ToString() + "," + node.Value.Label + "\r\n");
                }                
            }
            File.WriteAllText(nodesFilename, csv.ToString());
            //Creating edges file
            csv.Clear();
            using (File.Create(edgesFilename))
            {
                csv.Append("Source,Target,Type,Id,Label,Weight\r\n");
                foreach (KeyValuePair<Tuple<int, int>, Edge> edge in edges)
                {
                    csv.Append(edge.Value.SourceId + "," + edge.Value.TargetId + ",Directed," +
                               edge.Value.Id + "," + edge.Value.Label + "," + edge.Value.Weight.ToString() + "\r\n");
                }                
            }
            File.WriteAllText(edgesFilename, csv.ToString());
        }
    }

    public class Node
    {
        public int Id { get; set; }
        public String Label { get; set; }

        public Node(int _Id, String _Label = "")
        {
            Id = _Id;
            Label = _Label;
        }
    }

    public class Edge
    {
        public int SourceId { get; set; }
        public int TargetId { get; set; }
        public int Id { get; set; }
        public String Label { get; set; }
        public int Weight { get; set; }

        public Edge(int _Id, int _SourceId, int _TargetId, String _Label = "", int _Weight = 0)
        {
            Id = _Id;
            SourceId = _SourceId;
            TargetId = _TargetId;
            Label = _Label;
            Weight = _Weight;
        }
    }
}
