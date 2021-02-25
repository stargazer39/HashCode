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
        public class Pizza
        {
            public string[] ingredients;
            public int index;
            public int index_now;
            public Pizza(int Index, string[] Ingredients)
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

        private static bool debug = false;
        static void Main(string[] args_)
        {
            DirectoryInfo d = new DirectoryInfo(".");
            foreach (FileInfo f in d.GetFiles("*.in"))
            {
                MainProg(f.FullName);
            }
            Console.ReadLine();
        } 
        static void MainProg(string inFile)
        {
            LineReader lr = new LineReader(inFile);
            StreamWriter sw = new StreamWriter($"{inFile.Split('.')[0]}.out");

            Console.WriteLine($"Currunt file : {inFile}");
            string[] args = lr.Next().Split(' ');
            int[] teams = new int[3];
            int totalMembers = 0;
            int totalPizzas;
            List<Pizza> pizzas = new List<Pizza>();

            Console.WriteLine($"Total Pizzas : {args[0]}");
            // Parsing the arguments
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

            //Show the total members
            for(int i = 0; i < 3; i++)
            {
                totalMembers += (teams[i] * (i + 2));
            }
            Console.WriteLine($"Total members: {totalMembers}");

            //Get pizzas from next lines
            string line;
            int orig_index = 0;
            while ((line = lr.Next()) != null)
            {
                string[] array = line.Trim().Split(' ');
                Pizza p = new Pizza(orig_index, array.Skip(1).ToArray());
                // Add to the list
                pizzas.Add(p);
                orig_index++;
            }

            // Show How many available
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

            // Sorting Pizza list
            List<Pizza> newPizzas = pizzas.OrderByDescending(o => o.ingredients.Length).ToList();

            // Pizza Selection Begin
            List<string> output = new List<string>();
            int[] pizzaDelivered = { 0,0,0 };

            while (true)
            {
                // Pizza is distributed from the most teams to least
                int max = teams.Max();
                int i = Array.IndexOf(teams, max);

                // Break when the teams array ends
                if (teams[i] == 0) break;
                if (debug) 
                { 
                    Console.WriteLine(i);
                    Console.WriteLine(String.Join("|", teams));
                } 

                // Destribution of pizza
                for(int j = 0; j < teams[i]; j++)
                {
                    string tmp;
                    //Chck if next team can get pizza otherwise brake
                    if (newPizzas.Count < i + 2) break;

                    tmp = $"{i + 2} ";
                    // Get the unique pizza using algorithm
                    List<Pizza> pizz = PizzaMaker(i+2, newPizzas);

                    // Add them to the list
                    foreach (Pizza p in pizz)
                    {
                        tmp += $"{p.index} ";
                        if(debug) Console.WriteLine($"{p.index} {String.Join(" ", p.ingredients)}");
                    }
                    output.Add(tmp);
                    pizzaDelivered[i] += pizz.Count;

                    if(debug) Console.WriteLine("\n");
                }
                teams[i] = 0;
            }

            // Finally write all the output to a file
            sw.WriteLine(output.Count);
            foreach(string str in output)
            {
                sw.WriteLine(str);
            }
            sw.Flush();
            sw.Close();

            // Show the delivery info
            int totalDelivery = 0;
            for(int k = 0; k < 3; k++)
            {
                totalDelivery += pizzaDelivered[k];
                Console.WriteLine($"Delivered {pizzaDelivered[k]} to {k+2} member teams.");
            }
            Console.WriteLine($"Total pizzas : {totalDelivery}");
            Console.WriteLine("Done.\n");
        }
        //Pizza selection function
        public static Pizza UniquePizza(List<Pizza> pizzaList,Pizza pizzaCompare)
        {
            int intersect_length = 0;
            Pizza next_pizza = null;
            int next_index = 0;
            for(int i = 0; i <pizzaList.Count; i++)
            {
                // Compare the pizzas with the supplied ingredients (the union of all last pizzas)
                string[] intersect_ingredients = pizzaList[i].ingredients.Intersect(pizzaCompare.ingredients).ToArray();

                // Store the first length of intersection array
                if(i == 0)
                {
                    intersect_length = intersect_ingredients.Length;
                    continue;
                }

                // If intersection length of next pizza is lower, store it
                if(intersect_length >= intersect_ingredients.Length)
                {
                    next_pizza = pizzaList[i];
                    next_index = i;
                    //If the intersection is 0, the selected pizza must be unique. break the loop.
                    if (intersect_ingredients.Length == 0) break;
                }
            }
            // Incase no pizza is unique enough, return the first pizza (the higest ingregredient one)
            if(next_pizza == null)
            {
                next_pizza = pizzaList[0];
                next_index = 0;
            }
            // The current index of the sorted array is stored here for later use.
            next_pizza.index_now = next_index;
            return next_pizza;
        }
        // Pizza maker retuns pizza for specified count of pizza
        public static List<Pizza> PizzaMaker(int members,List<Pizza> pizzaList)
        {
            List<Pizza> output = new List<Pizza>();
            string[] uni_ingredients = null;
            string[] uni_ingredients2 = null;
            // Pizza for each member
            for (int i = 0; i < members - 1; i++)
            {
                if(i == 0)
                {
                    // For the first pizza, compare it eith the most ingredient one. (the 0th index)
                    Pizza next = UniquePizza(pizzaList, pizzaList[0]);
                    // Add to output
                    output.Add(pizzaList[0]);
                    output.Add(next);
                    // Remove the 0th one
                    pizzaList.RemoveAt(0);
                    // Compensating for 'only one pizza left in the list'. and remove the added pizza
                    if(next.index_now != 0) pizzaList.RemoveAt(next.index_now - 1);
                    continue;
                }
                if(i == 1)
                {
                    // Get union of currently selected pizzas
                    uni_ingredients = output[0].ingredients.Union(output[1].ingredients).ToArray();
                    // Compare union with the pizza list
                    Pizza next = UniquePizza(pizzaList, new Pizza(-1,uni_ingredients));
                    // Add and Remove
                    output.Add(next);
                    pizzaList.RemoveAt(next.index_now);
                    continue;
                }
                if(i == 2)
                {
                    // Get union of currently selected pizzas
                    uni_ingredients2 = uni_ingredients.Union(output[2].ingredients).ToArray();
                    // Compare union with the pizza list
                    Pizza next = UniquePizza(pizzaList, new Pizza(-1, uni_ingredients2));
                    // Add and Remove
                    output.Add(next);
                    pizzaList.RemoveAt(next.index_now);
                }
            }
            // Return the output
            return output;
        }
        
    }
}
