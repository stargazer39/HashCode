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
        static void Main(string[] args_)
        {
            LineReader lr = new LineReader("d_many_pizzas.in");
            StreamWriter sw = new StreamWriter("out.txt");
            string[] args = lr.Next().Split(' ');
            int[] teams = new int[4];
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
            List<Pizza> newPizzas = pizzas.OrderByDescending(o => o.ingredients.Length).ToList();
            foreach(Pizza p in newPizzas)
            {
                sw.WriteLine($"{p.index} {String.Join(" ", p.ingredients)}");
            }
            sw.Flush();
            sw.Close();
            Pizza max_ingredient = null;
            Pizza next = null;
            int min_inter = -1;
            for(int i = 0; i < newPizzas.Count - 1; i++)
            {
                string[] intersect = null;
                //Console.WriteLine(String.Join(" ",union));
                if(min_inter == -1)
                {
                    max_ingredient = newPizzas[i];
                    intersect = max_ingredient.ingredients.Intersect(newPizzas[i + 1].ingredients).ToArray();
                    min_inter = intersect.Length;
                    //Debug.WriteLine($"inter {intersect.Length}");
                    continue;
                }
                intersect = max_ingredient.ingredients.Intersect(newPizzas[i + 1].ingredients).ToArray();
                //Debug.WriteLine($"inter {intersect.Length}");
                if (intersect.Length < min_inter)
                {
                    min_inter = intersect.Length;
                    next = newPizzas[i+1];
                }
            }
            Console.WriteLine($"{max_ingredient.index},{next.index} {String.Join(" ", max_ingredient.ingredients)} // {String.Join(" ", next.ingredients)}");
            //for(int i = 0; i < newPizzas.Count())
            Console.ReadKey();
        }
        public class Pizza
        {
            public string[] ingredients;
            public int index;
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
