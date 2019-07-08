import csv

file = open('MAPA TESTE._Decoração Backgrounder.txt', 'w')
with open('Teste_Decoração Backgrounder.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    columns_nro = 0
    for row in csv_reader:
        columns_nro += 1
        rows_nro = 0
        for element in row:
            rows_nro += 1
    file.write("{0:0=3d}".format(rows_nro) + ',' + "{0:0=3d}".format(columns_nro) + ',1,\n')
    file.write("\n")
with open('Teste_Decoração Backgrounder.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    columns_nro = 0
    for row in csv_reader:
        for element in row:
            nro = int(element, 10) + 1
            string = "{0:0=3d}".format(nro)
            file.write(string + ',')
        file.write("\n")
    file.close()
