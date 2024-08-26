var builder = WebApplication.CreateBuilder(args);

builder.Services.LoadAssembly("UserStores"); // �ؼӣ����������µ���Ŀ���������һ��
builder.Services.ScanAllDependency(); // �ؼ�
builder.Services.AddMvc();
builder.Services.AddSqliteDatabase(@".\myDb.db", "UserAuthen"); //�����UserAuthen��Ĭ����Ŀ�����֣�����ʵ������޸�

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Error");
}
app.UseStaticFiles();

app.UseRouting();
app.MapControllers();

app.Run();
