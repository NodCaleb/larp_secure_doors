// See https://aka.ms/new-console-template for more information


var codes = File.ReadAllLines(@"D:\Sources\larp_secure_doors\codes.txt");

var arrays = new List<string>();

foreach (var code in codes)
{
	arrays.Add($"{{'{code[0]}', '{code[1]}', '{code[2]}', '{code[3]}'}},");
}

File.WriteAllLines(@"D:\Sources\larp_secure_doors\arrays.txt", arrays);

Console.WriteLine("Cmoplete!");