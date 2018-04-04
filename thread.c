
using System;

using System.Collections.Generic;

using System.Linq;

using System.Text;

using System.Threading;

using System.Threading.Tasks;

using System.Collections;

using System.Collections.Concurrent;


namespace seqBythread

{

    class Program

    {

        static int status;
        static bool running ;
        static Thread t = new Thread(th);
        static ConcurrentQueue<int> q = new ConcurrentQueue<int>();
        
        static AutoResetEvent e = new AutoResetEvent(false);
       // static int[] buf = new int[4] { 1, 1, 2, 3 };
        

        public static int fsm_init()
        {

            status = 0;
            return 0;
        }

        static void Main(string[] args)

        {
            int a = 0;
            int ret = 0;
            t.Start();
            // int a =0;
            //str1.Console.readLine();
            //String str1=Console.ReadLine();
            //a = Convert.ToInt32(str1);
            status = 0;
            while(running == true)
            {

                do
                {
                    e.WaitOne();
                    //status = fsm_init();

                    int cnt;
                    cnt = q.Count;

                    for (int j = 0; j < cnt; j++)

                    {
                        q.TryDequeue(out a);
                        Console.WriteLine("Dequeue q : {0}", a);
                        Console.WriteLine("number is : " + a);
                        ret = fsm_update(a);
                        Console.WriteLine("status " + status);
                    }
                    Console.WriteLine("--------------");
                    //printValues(q);

                } while (ret == 0 && running == true);

            }
            if(running == false)
            {

                t.Join();

            }
                
            
            
           
        }

        //if the number was in our array 
       public static int fsm_update(int num)
        {
            // status = fsm_init();
            Console.WriteLine(num + "," + status);
                switch (status)
                {

                case 0 : //A
                    if (num == 1)
                    {
                        Console.WriteLine("0 -> 1");
                        status = 1;
                       
                        Console.WriteLine("current status"+status);
                    }
                    else
                    {
                        status = 0;
                    }
                    break;
                    
                case 1: //B

                    if (num == 1)
                    {
                        status = 2;
                        //curr_status(status);

                    }
                    else
                    {

                        status = 0;

                    }
                    break;
  
                case 2: //C


                    if (num == 2)
                    {
                        status = 3;
                        
                    }
                    else
                    {
                        if (num == 1)
                        {
                            status = 2;
                        }
                        else
                            status = 0;


                    }


                    break;

                case 3: //D
                    if (num == 3)
                    {
                        status=4;
                        
                    }
                    else
                        status = 0;

                    break;



                case 4: 
                    if (num == 5)
                    {
                        status = 5;

                    }
                    else
                        status = 0;

                    break;

                case 5:
                    if (num == 8)
                    {
                        return 1;

                    }
                    else
                        status = 0;

                    break;
            }

            return 0;

          

        }

        

        public static void th()

        {

            int num = 0;
            
            String name = Thread.CurrentThread.Name;

            Console.WriteLine("waiting on AutoResetEvent :", name);

            Console.WriteLine("Insert numbers:");
            Random rnd = new Random();

            // do

           
            do{



                //String str = Console.ReadLine();

                num = 0;

                try

                {
                    while (running == true)
                    {


                    q.Enqueue(rnd.Next(1, 9));
                   Console.WriteLine("Enqueue : {0}", num);
                     e.Set();

                    }
                    //num = Convert.ToInt32(str);
                    //q.Enqueue(num);
                    
                }
                catch (Exception ex)

                {

                    Console.WriteLine("Exception: " + ex.Message);

                }



            } while (num != -1);

            
                


            Console.WriteLine("Exiting..");


        }



        private static void printValues(ConcurrentQueue<int> q)

        {

            foreach (Object obj in q)

            {

                Console.WriteLine("{0}", obj);

            }

        }

    }

}
