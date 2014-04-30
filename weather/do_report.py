import os
import shutil
import time
import subprocess
from subprocess import Popen, PIPE, STDOUT

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

    f.write("<tr><td>")
    f.write(city)
    f.write("</td><td>")
    f.write(temperature)
    f.write("</td><td>")
    f.write(humidity)
    f.write("</td><td>")
    f.write(wind)
    f.write("</td><td>")
    f.write(conditions)
    f.write("</td></tr>")

    f.close()

def write_error(city):
    f = open('./report.html', 'a')
    f.write("<tr><td>")
    f.write(city)
    f.write("</td><td>No data received")
    f.write("</td><td></td><td></td><td></td></tr>")
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
    cmdline = ["/usr/bin/weather", code]

    output = None
    try:
        output = subprocess.check_output(cmdline)
    except Exception as e:
        raise Exception("Error retrieving data")
    print("Output is:")
    print(output)
    return output

def do_report(city, code):
    trying = True
    tries = 1
    output = None
    while (trying == True):
        try:
            print("Fetching data (#attempt " + str(tries) + ")")
            output = fetch_data(code)
            trying = False
        except Exception as e:
            print(e)
            tries += 1
            if (tries >= 4):
                trying = False
                print("Giving up after 4 tries. Writing error to output")
                write_error(city)
                return

    write_row(output, city)
    time.sleep(1)

def prepare():
    try:
        shutil.copy("./template.html", "./report.html")
        print("Successfully copied template file")
    except IOError as e:
        print(e)

def upload():
    try:
        shutil.copy("./report.html", "/home/gekko/public_html/weather/index.html")
        print("Successfully uploaded the report")
        os.chmod("/home/gekko/public_html/weather/index.html", 0775)
    except IOError as e:
        print(e)

prepare()
do_report("Clarksville (Ranti)", "KCKV")
do_report("Turku (Gekko)", "EFTU")
do_report("Tampere", "EFTP")
do_report("Kuopio", "EFKU")
do_report("Oulu", "EFOU")
do_report("Helsinki", "EFHK")
do_report("Moscow (Xai)", "UUEE")
do_report("Palanga (Rytis)", "EYPA")
do_report("Kansas City (Dritz)", "KMCI")
do_report("North Vancouver (AmonX)", "CYVR")
do_report("Detroit (Oldlaptop)", "KDTW")
do_report("Miami (Ziper)", "KMIA")
do_report("Bagotville (Blue)", "CYBG")
do_report("Florianopolis (Yohan)", "SBFL")
do_report("Chennai", "VOMM")
do_report("Dusseldorf (Vrad)", "EDDL")
do_report("Melbourne (chaos95)", "YMML")
finish_document()
upload()

