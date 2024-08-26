using Framework;
using System.Reflection;

namespace Microsoft.Extensions.DependencyInjection
{
    public static class DependencyExtension
    {
        public static void LoadAssembly(this IServiceCollection collection, string assemblyName)
        {
            Assembly.Load(assemblyName);
        }

        public static void ScanAllDependency(this IServiceCollection collection)
        {
            ModuleInitializer initializer = new ModuleInitializer(collection);
            initializer.InitializeAssembly();
        }
    }
}
