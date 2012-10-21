import os
import shutil

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
    f.write("</table><br><br>")

    output = ""
    process = os.popen("/bin/date", "r")
    while 1:
        line = process.readline()
        if not line: break
        output += line
    f.write("Data generated ")
    f.write(output)
    f.write("</body></html>")
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
    try:
        shutil.copy("./template.html", "./report.html")
        print("Successfully copied template file")
    except IOError as e:
        print(e)

    output = ""
    process = os.popen("/bin/date", "r")
    while 1:
        line = process.readline()
        if not line: break
        output += line
    f = open("./report.html", 'a')
    f.write("Data generated ")
    f.write(output)
    f.close()

def upload():
    try:
        shutil.copy("./report.html", "/home/gekko/public_html/weather/index.html")
        print("Successfully uploaded the report")
        os.chmod("/home/gekko/public_html/weather/index.html", 0775)
    except IOError as e:
        print(e)

prepare()
do_report("Turku")
do_report("Clarksville")
finish_document()
upload()

