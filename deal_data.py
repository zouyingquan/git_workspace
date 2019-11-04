
import xlrd
import xlwt

class CityData:
    #这里存放的是数据类型，比如，结婚，离婚，年末总人口数（万人），非农业人口数（万人），等等
   def __init__(self):
      self.marry = []                               #存放的是结婚的
      self.divorce = []                             #存放的是离婚的
      self.year = []                                #存放的是年份对应的索引
      self.total_population = []                    #存放的是年末总人口数（万人）
      self.total_nonagricultural_population = []    #存放的是非农业人口总数（万人）
      self.Unemployment = []
      self.gdp = []
      self.pgdp = []
      self.first_industry = []
      self.second_industry = []
      self.thrid_industry = []
      self.people_highschool = []                   #普通高等学校在校学生数（人）
      self.people_midschool = []                    #普通中学在校学生数（1993-1996年为中等学校）（万人）
      self.people_primaryschool = []                #小学在校学生数（万人）
      self.highschoollevel = []                     #高中阶段在校学生数（人）
      self.midTecSchool = []                        #中等职业技术学校在校学生数（人）
      self.students_in_adult_colleges = []               #成人高等学校在校学生数（人）
      self.college_students_per_m = []                   #每万人在校大学生数（人）
      self.secondary_vocational_students_per_m = []      #每万人在校中等职业学生数（人）
   def printMarry(self):
      print(self.marry)
   def printDivorce(self):
      print(self.divorce)

def read_data(name,data,):
    rd = xlrd.open_workbook(filename)
    sheet = rd.sheet_by_index(0)
    type = 0 # 0 -> marry, 1 -> divorce，2->年末总人口数（万人）,3->非农业人口数（万人）,以此类推
    print(sheet.name)

    data.year = sheet.row_values(0)


    for i in range(1,sheet.nrows):
        rows = sheet.row_values(i)
        if rows[0] != None and rows[0] == '年末总人口数（万人）':
            type = 0
        elif rows[0] != None and rows[0] == '非农业人口数（万人）':
            type = 1
        elif rows[0] != None and rows[0] == '年末城镇登记失业人员数（人）':
            type = 2
        elif rows[0] != None and rows[0] == '地区生产总值（万元）':
            type = 3
        elif rows[0] != None and rows[0] == '人均地区生产总值（元）':
            type = 4
        elif rows[0] != None and rows[0] == '第一产业增加值（万元）':
            type = 5
        elif rows[0] != None and rows[0] == '第二产业增加值（万元）':
            type = 6
        elif rows[0] != None and rows[0] == '第三产业增加值（万元）':
            type = 7
        elif rows[0] != None and rows[0] == '普通高等学校在校学生数（人）':
            type = 8
        elif rows[0] != None and rows[0] == '普通中学在校学生数（1993-1996年为中等学校）（万人）':
            type = 9
        elif rows[0] != None and rows[0] == '小学在校学生数（万人）':
            type = 10
        elif rows[0] != None and rows[0] == '高中阶段在校学生数（人）':
            type = 11
        elif rows[0] != None and rows[0] == '中等职业技术学校在校学生数（人）':
            type = 12
        elif rows[0] != None and rows[0] == '成人高等学校在校学生数（人）':
            type = 13
        elif rows[0] != None and rows[0] == '每万人在校大学生数（人）':
            type = 14
        elif rows[0] != None and rows[0] == '每万人在校中等职业学生数（人）':
            type = 15
            
            
        if type == 0: #结婚的数据
            data.total_population.append(rows)
        elif type == 1:
            data.total_nonagricultural_population.append(rows)
        elif type == 2:
            data.Unemployment.append(rows)
        elif type == 3:
            data.gdp.append(rows)
        elif type == 4:
            data.pgdp.append(rows)
        elif type == 5:
            data.first_industry.append(rows)
        elif type == 6:
            data.second_industry.append(rows)
        elif type == 7:
            data.thrid_industry.append(rows)
        elif type == 8:
            data.people_highschool.append(rows)
        elif type == 9:
            data.people_midschool.append(rows)
        elif type == 10:
            data.people_primaryschool.append(rows)
        elif type == 11:
            data.highschoollevel.append(rows)
        elif type == 12:
            data.midTecSchool.append(rows)
        elif type == 13:
            data.students_in_adult_colleges.append(rows)
        elif type == 14:
            data.college_students_per_m.append(rows)
        elif type == 15:
            data.secondary_vocational_students_per_m.append(rows)

        #print(rows)
        
        
def isCityExist(city,data):
    if city == None:
        print('ctiy is none')
        return -1
    for i in range(0,len(data)):
        if city == data[i][1]:
            return i
    return -1
      
def writeData(name,data):
   wt = xlwt.Workbook()
   write_sheet = wt.add_sheet('sheet1')
   title = ['城市','年份','年末总人口数（万人）','非农业人口数（万人）','年末城镇登记失业人员数（人）','地区生产总值（万元）','人均地区生产总值（元）','第一产业增加值（万元）','第二产业增加值（万元）','第三产业增加值（万元）','普通高等学校在校学生数（人）','普通中学在校学生数（1993-1996年为中等学校）（万人）','小学在校学生数（万人）','高中阶段在校学生数（人）','中等职业技术学校在校学生数（人）','成人高等学校在校学生数（人）','每万人在校大学生数（人）','每万人在校中等职业学生数（人）']
   for i in range(0,len(title)):
      write_sheet.write(0,i,title[i])
   
   x = 0
   index = -1
   for i in range(0,len(data.total_population)):
      print(i)
      for j in range(2,len(data.total_population[i])):
         #if data.marry[i][j] != '' or data.divorce[i][j] != '':
            #print(data.year[j])
            #print(data.marry[i][j])
        #print(data.first_industry[i][1])
        #print(str(i) + '---' + str(j))
        x += 1
        city = data.total_population[i][1] #城市名称
        write_sheet.write(x,0,city) 
        write_sheet.write(x,1,data.year[j])
        write_sheet.write(x,2,data.total_population[i][j])
        
        index = isCityExist(city,data.total_nonagricultural_population)
        if index != -1:
            print(index)
            write_sheet.write(x,3,data.total_nonagricultural_population[index][j])
            
        index = isCityExist(city,data.Unemployment)  
        if index != -1:
            write_sheet.write(x,4,data.Unemployment[index][j])    
           
        index = isCityExist(city,data.gdp)  
        if index != -1:
            write_sheet.write(x,5,data.gdp[index][j])    
            
        index = isCityExist(city,data.pgdp)
        if index != -1:
            write_sheet.write(x,6,data.pgdp[index][j])   
           
        index = isCityExist(city,data.first_industry)
        if index != -1:
            write_sheet.write(x,7,data.first_industry[index][j])   


        index = isCityExist(city,data.second_industry)
        if index != -1:
            write_sheet.write(x,8,data.second_industry[index][j])  
    
        
        index = isCityExist(city,data.thrid_industry)
        if index != -1:
            write_sheet.write(x,9,data.thrid_industry[index][j])  
         
        index = isCityExist(city,data.people_highschool)
        if index != -1:
            write_sheet.write(x,10,data.people_highschool[index][j])  
          

        index = isCityExist(city,data.people_midschool)  
        if index != -1:
            write_sheet.write(x,11,data.people_midschool[index][j])  
            
        index = isCityExist(city,data.people_primaryschool)
        if index != -1:
            write_sheet.write(x,12,data.people_primaryschool[index][j]) 
            
        index = isCityExist(city,data.highschoollevel)  
        if index != -1:
            write_sheet.write(x,13,data.highschoollevel[index][j])  
            
        index = isCityExist(city,data.midTecSchool)
        if index != -1:
            write_sheet.write(x,14,data.midTecSchool[index][j])  
            
        index = isCityExist(city,data.students_in_adult_colleges)   
        if index != -1:
            write_sheet.write(x,15,data.students_in_adult_colleges[index][j])  
            
        index = isCityExist(city,data.college_students_per_m)    
        if index != -1:
            write_sheet.write(x,16,data.college_students_per_m[index][j]) 
            
        index = isCityExist(city,data.secondary_vocational_students_per_m)   
        if index != -1:
            write_sheet.write(x,17,data.secondary_vocational_students_per_m[index][j])  
            
            
            
   wt.save(name)

filename = '2.xls'
result = '2_ans.xlsx'
marry_flag = '内地居民登记结婚（对）'
divorce_flag = '登记离婚数（对）'
data = CityData()
read_data(filename,data)
#data.printMarry()
print(data.total_population)
print(len(data.total_population))
#print(data.first_industry[9][35])
writeData(result,data)

