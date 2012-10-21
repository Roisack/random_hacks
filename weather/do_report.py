import os

def write_row(data, place):
    f = open('./report.html', 'a')
    list_of_lines = data.split('\n')

    city = place
    temperature = ""
    wind = ""
    humidity = ""
    conditions = ""

    for l in list_of_lines:
        if ("Temperature" in l):
            temperature = l
            #temperature = temperature[len("Temperature: ")+3:len(temperature)]
        elif ("Relative Humidity" in l):
            humidity = l
            #humidity = humidity[len("Relative Humidity: ")+3:len(humidity)]
        elif ("Wind" in l):
            wind = l
            #wind = wind[len("Wind: ")+3:len(wind)]
        elif ("Sky conditions" in l):
            conditions = l
            #conditions = conditions[len("Sky conditions: ")+3:len(conditions)]

    f.write("<tr><th>")
    f.write(city)
    f.write("</th><th>")
    f.write(temperature)
    f.write("</th><th>")
    f.write(wind)
    f.write("</th><th>")
    f.write(humidity)
    f.write("</th><th>")
    f.write(conditions)
    f.write("</th></tr>")

    f.close()

def finish_document():
    print("Finishing document")
    f = open('./report.html', 'a')
    f.write("</table></body></html>")
    f.close()

def fetch_data(code): 
    cmdline = "./weather.sh "
    cmdline += code
    process = os.popen(cmdline, "r")
    output = ""
    while 1:
        line = process.readline()
        if not line: break
        output += line
    return output

def do_report(city):
    if (city == "Turku"):
        output = fetch_data("EFTU")
    elif (city == "Clarksville"):
        output = fetch_data("KCKV")
    else:
        print("No codes given for " + city)
        return

    print("Writing data for " + city)
    write_row(output, city)

def prepare():
    os.popen('/bin/cp ./template.html ./report.html', "r")

prepare()
do_report("Turku")
do_report("Clarksville")

finish_document()
