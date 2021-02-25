using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace HashCode
{
    class Program
    {
        public static string inFile = "d_many_pizzas.in";
        static void Main(string[] args_)
        {
            LineReader lr = new LineReader(inFile);
            StreamWriter sw = new StreamWriter($"{inFile.Split('.')[0]}.out");
            string[] args = lr.Next().Split(' ');
            int[] teams = new int[3];
            int totalMembers = 0;
            int totalPizzas;
            List<Pizza> pizzas = new List<Pizza>();
            Console.WriteLine($"Total Pizzas : {args[0]}");
            for(int i = 0; i < 4; i++)
            {
                if(i == 0)
                {
                    Int32.TryParse(args[i], out totalPizzas);
                    continue;
                }
                Int32.TryParse(args[i], out teams[i - 1]);
                Console.WriteLine($"Teams with {i + 1} members : {args[i]}");
            }
            for(int i = 0; i < 3; i++)
            {
                totalMembers += (teams[i] * (i + 2));
            }
            Console.WriteLine($"Total members: {totalMembers}");
            string line;
            int orig_index = 0;
            while ((line = lr.Next()) != null)
            {
                string[] array = line.Trim().Split(' ');
                Pizza p = new Pizza(orig_index, array.Skip(1).ToArray());
                pizzas.Add(p);
                orig_index++;
            }
            /// Show How many available
            Console.WriteLine(String.Join(" ",teams));
            if (totalMembers > pizzas.Count)
            {
                Console.WriteLine($"\nOnly {pizzas.Count} pizza available. ");
            }
            else if (totalMembers == pizzas.Count)
            {
                Console.WriteLine($"There's just enough pizza for everyone.");
            }
            else
            {
                Console.WriteLine($"There's more pizza ({pizzas.Count}) than members ({totalMembers}). Grate.");
            }

            List<Pizza> newPizzas = pizzas.OrderByDescending(o => o.ingredients.Length).ToList();
            List<string> output = new List<string>();
            /*foreach(Pizza p in newPizzas)
            {
                sw.WriteLine($"{p.index} {String.Join(" ", p.ingredients)}");
            }
            sw.Flush();
            sw.Close();*/

            /// Pizza Selection Begin
            for(int i = 0; i <= 2; i++)
            {
                for(int j = 0; j < teams[i]; j++)
                {
                    if (newPizzas.Count < i + 2) break;
                    string tmp;
                    tmp = $"{i + 2} ";
                    //sw.Write($"{i+2} ");
                    List<Pizza> pizz = PizzaMaker(i+2, newPizzas);
                    foreach (Pizza p in pizz)
                    {
                        //sw.Write($"{p.index} ");
                        tmp += $"{p.index} ";
                        Console.WriteLine($"{p.index} {String.Join(" ", p.ingredients)}");
                    }
                    output.Add(tmp);
                    //sw.Write("\n");
                    Console.WriteLine("\n");
                }
            }
            sw.WriteLine(output.Count);
            foreach(string str in output)
            {
                sw.WriteLine(str);
            }
            sw.Flush();
            sw.Close();

            /* Console.WriteLine("\n");
             Debug.WriteLine(newPizzas.Count);
             pizz = PizzaMaker(2, newPizzas);
             foreach (Pizza p in pizz)
             {
                 Console.WriteLine($"{p.index} {String.Join(" ", p.ingredients)}");
             }*/
            Console.WriteLine("Done.");
            //Console.WriteLine($"{newPizzas[0].index},{next.index} {String.Join(" ", newPizzas[0].ingredients)} // {String.Join(" ", next.ingredients)}");
            //for(int i = 0; i < newPizzas.Count())
            Console.ReadLine();
        }
        public static Pizza UniquePizza(List<Pizza> pizzaList,Pizza pizzaCompare)
        {
            int intersect_length = 0;
            Pizza next_pizza = null;
            int next_index = 0;
            for(int i = 0; i <pizzaList.Count; i++)
            {
                string[] intersect_ingredients = pizzaList[i].ingredients.Intersect(pizzaCompare.ingredients).ToArray();
                if(i == 0)
                {
                    intersect_length = intersect_ingredients.Length;
                    continue;
                }
                if(intersect_length > intersect_ingredients.Length)
                {
                    next_pizza = pizzaList[i];
                    next_index = i;
                    if (intersect_ingredients.Length == 0) break;
                }
            }
            if(next_pizza == null)
            {
                next_pizza = pizzaList[0];
                next_index = 0;
            }
            next_pizza.index_now = next_index;
            return next_pizza;
        }
        public static List<Pizza> PizzaMaker(int members,List<Pizza> pizzaList)
        {
            List<Pizza> output = new List<Pizza>();
            string[] uni_ingredients = null;
            string[] uni_ingredients2 = null;
            for (int i = 0; i < members - 1; i++)
            {
                if(i == 0)
                {
                    Pizza next = UniquePizza(pizzaList, pizzaList[0]);
                    output.Add(pizzaList[0]);
                    output.Add(next);
                    pizzaList.RemoveAt(0);
                    if(next.index_now != 0) pizzaList.RemoveAt(next.index_now - 1);
                    continue;
                }
                if(i == 1)
                {
                    uni_ingredients = output[0].ingredients.Union(output[1].ingredients).ToArray();
                    Pizza next = UniquePizza(pizzaList, new Pizza(-1,uni_ingredients));
                    output.Add(next);
                    pizzaList.RemoveAt(next.index_now);
                    continue;
                }
                if(i == 2)
                {
                    uni_ingredients2 = uni_ingredients.Union(output[2].ingredients).ToArray();
                    Pizza next = UniquePizza(pizzaList, new Pizza(-1, uni_ingredients2));
                    output.Add(next);
                    pizzaList.RemoveAt(next.index_now);
                }
            }
            return output;
        }
        public class Pizza
        {
            public string[] ingredients;
            public int index;
            public int index_now;
            public Pizza(int Index,string[] Ingredients)
            {
                ingredients = Ingredients;
                index = Index;
            }
        }
        public class LineReader
        {
            public StreamReader sr;
            public string file_;
            public LineReader(string file)
            {
                file_ = file;
                sr = new StreamReader(file);
                sr.BaseStream.Seek(0, SeekOrigin.Begin);
            }
            public string Next()
            {
                return sr.ReadLine();
            }
        }
    }
}
