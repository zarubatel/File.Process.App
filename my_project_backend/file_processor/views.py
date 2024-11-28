from django.shortcuts import render

import os
from django.shortcuts import render, redirect
from django.conf import settings
from .models import File
from subprocess import Popen, PIPE


def upload_file(request):
    if request.method == 'POST':
        file_obj = request.FILES.get('file')
        if file_obj:
            file_path = os.path.join(settings.MEDIA_ROOT, file_obj.name)
        
            with open(file_path, 'wb+') as destination:
                for chunk in file_obj.chunks():
                        destination.write(chunk)
                        
            # Обработка файла через внешний модуль на C++
            process = Popen(['./process_file', file_path], stdout=PIPE, stderr=PIPE)
            output, error = process.communicate()
            
            if error:
                print(f'Ошибка при обработке файла: {error.decode("utf-8")}')
            else:
                result = output.decode('utf-8')
                
                # Сохранение результата в базу данных
                file_model = File(filename=file_obj.name, result=result)
                file_model.save()
        else:
            print('Необходимо выбрать файл для загрузки.')
    files = File.objects.all().order_by('-uploaded_at')
    context = {'files': files}
    return render(request, 'upload.html', context)